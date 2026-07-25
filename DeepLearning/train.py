"""Train and evaluate a CNN on MNIST."""

import argparse
import random
from pathlib import Path

import torch
from torch import nn
from torch.utils.data import DataLoader, Subset
from torchvision import datasets, transforms

from model import DigitCNN

MNIST_MEAN = 0.1307
MNIST_STD = 0.3081


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Train an MNIST digit classifier")
    parser.add_argument("--epochs", type=int, default=5)
    parser.add_argument("--batch-size", type=int, default=128)
    parser.add_argument("--learning-rate", type=float, default=1e-3)
    parser.add_argument("--data-dir", type=Path, default=Path("data"))
    parser.add_argument("--model-path", type=Path, default=Path("checkpoints/mnist_cnn.pt"))
    parser.add_argument("--seed", type=int, default=42)
    parser.add_argument("--cpu", action="store_true", help="Force training on the CPU")
    parser.add_argument(
        "--max-train-samples",
        type=int,
        default=None,
        help="Limit training samples for a quick smoke test",
    )
    parser.add_argument(
        "--max-test-samples",
        type=int,
        default=None,
        help="Limit test samples for a quick smoke test",
    )
    return parser.parse_args()


def choose_device(force_cpu: bool) -> torch.device:
    if not force_cpu and torch.cuda.is_available():
        return torch.device("cuda")
    return torch.device("cpu")


def create_loaders(args: argparse.Namespace, use_cuda: bool):
    transform = transforms.Compose(
        [
            transforms.ToTensor(),
            transforms.Normalize((MNIST_MEAN,), (MNIST_STD,)),
        ]
    )
    train_data = datasets.MNIST(args.data_dir, train=True, download=True, transform=transform)
    test_data = datasets.MNIST(args.data_dir, train=False, download=True, transform=transform)

    if args.max_train_samples is not None:
        train_data = Subset(train_data, range(min(args.max_train_samples, len(train_data))))
    if args.max_test_samples is not None:
        test_data = Subset(test_data, range(min(args.max_test_samples, len(test_data))))

    loader_options = {
        "batch_size": args.batch_size,
        "num_workers": 0,
        "pin_memory": use_cuda,
    }
    train_loader = DataLoader(train_data, shuffle=True, **loader_options)
    test_loader = DataLoader(test_data, shuffle=False, **loader_options)
    return train_loader, test_loader


def train_one_epoch(model, loader, loss_fn, optimizer, device):
    model.train()
    total_loss = 0.0
    total_correct = 0

    for images, labels in loader:
        images = images.to(device, non_blocking=True)
        labels = labels.to(device, non_blocking=True)

        optimizer.zero_grad()
        logits = model(images)
        loss = loss_fn(logits, labels)
        loss.backward()
        optimizer.step()

        total_loss += loss.item() * labels.size(0)
        total_correct += (logits.argmax(dim=1) == labels).sum().item()

    sample_count = len(loader.dataset)
    return total_loss / sample_count, total_correct / sample_count


@torch.inference_mode()
def evaluate(model, loader, loss_fn, device):
    model.eval()
    total_loss = 0.0
    total_correct = 0

    for images, labels in loader:
        images = images.to(device, non_blocking=True)
        labels = labels.to(device, non_blocking=True)
        logits = model(images)
        total_loss += loss_fn(logits, labels).item() * labels.size(0)
        total_correct += (logits.argmax(dim=1) == labels).sum().item()

    sample_count = len(loader.dataset)
    return total_loss / sample_count, total_correct / sample_count


def main() -> None:
    args = parse_args()
    if args.epochs < 1 or args.batch_size < 1:
        raise ValueError("epochs and batch-size must be positive")

    random.seed(args.seed)
    torch.manual_seed(args.seed)
    device = choose_device(args.cpu)
    if device.type == "cuda":
        torch.cuda.manual_seed_all(args.seed)

    print(f"Device: {device}")
    if device.type == "cuda":
        print(f"GPU: {torch.cuda.get_device_name(0)}")

    train_loader, test_loader = create_loaders(args, device.type == "cuda")
    model = DigitCNN().to(device)
    loss_fn = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=args.learning_rate)
    best_accuracy = -1.0

    for epoch in range(1, args.epochs + 1):
        train_loss, train_accuracy = train_one_epoch(
            model, train_loader, loss_fn, optimizer, device
        )
        test_loss, test_accuracy = evaluate(model, test_loader, loss_fn, device)
        print(
            f"Epoch {epoch:02d}/{args.epochs} | "
            f"train loss {train_loss:.4f}, accuracy {train_accuracy:.2%} | "
            f"test loss {test_loss:.4f}, accuracy {test_accuracy:.2%}"
        )

        if test_accuracy > best_accuracy:
            best_accuracy = test_accuracy
            args.model_path.parent.mkdir(parents=True, exist_ok=True)
            torch.save(
                {
                    "model_state_dict": model.state_dict(),
                    "test_accuracy": test_accuracy,
                    "epoch": epoch,
                },
                args.model_path,
            )

    print(f"Best model: {args.model_path} (accuracy {best_accuracy:.2%})")


if __name__ == "__main__":
    main()
