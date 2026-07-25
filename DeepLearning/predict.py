"""Predict a handwritten digit from an image or an MNIST test sample."""

import argparse
from pathlib import Path

import torch
from PIL import Image, ImageOps
from torchvision import datasets, transforms

from model import DigitCNN
from train import MNIST_MEAN, MNIST_STD, choose_device


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Recognize one handwritten digit")
    parser.add_argument("--image", type=Path, help="Path to a handwritten digit image")
    parser.add_argument("--index", type=int, default=0, help="MNIST test index when no image is given")
    parser.add_argument("--data-dir", type=Path, default=Path("data"))
    parser.add_argument("--model-path", type=Path, default=Path("checkpoints/mnist_cnn.pt"))
    parser.add_argument("--cpu", action="store_true")
    return parser.parse_args()


def image_to_tensor(path: Path) -> torch.Tensor:
    if not path.is_file():
        raise FileNotFoundError(f"Image not found: {path}")

    image = Image.open(path).convert("L")
    image = ImageOps.fit(image, (28, 28), method=Image.Resampling.LANCZOS)

    # MNIST uses a dark background. Invert common black-on-white handwritten images.
    if sum(image.getdata()) / (28 * 28) > 127:
        image = ImageOps.invert(image)

    transform = transforms.Compose(
        [
            transforms.ToTensor(),
            transforms.Normalize((MNIST_MEAN,), (MNIST_STD,)),
        ]
    )
    return transform(image).unsqueeze(0)


def mnist_sample(data_dir: Path, index: int):
    dataset = datasets.MNIST(data_dir, train=False, download=True, transform=transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((MNIST_MEAN,), (MNIST_STD,)),
    ]))
    if not 0 <= index < len(dataset):
        raise IndexError(f"index must be between 0 and {len(dataset) - 1}")
    image, label = dataset[index]
    return image.unsqueeze(0), label


@torch.inference_mode()
def main() -> None:
    args = parse_args()
    if not args.model_path.is_file():
        raise FileNotFoundError(f"Model not found: {args.model_path}. Run train.py first.")

    device = choose_device(args.cpu)
    checkpoint = torch.load(args.model_path, map_location=device, weights_only=True)
    model = DigitCNN().to(device)
    model.load_state_dict(checkpoint["model_state_dict"])
    model.eval()

    expected = None
    if args.image:
        image = image_to_tensor(args.image)
        source = str(args.image)
    else:
        image, expected = mnist_sample(args.data_dir, args.index)
        source = f"MNIST test sample {args.index}"

    probabilities = model(image.to(device)).softmax(dim=1)[0]
    top_probabilities, top_digits = probabilities.topk(3)

    print(f"Source: {source}")
    print(f"Prediction: {top_digits[0].item()}")
    if expected is not None:
        print(f"Expected: {expected}")
    print("Top 3:")
    for digit, probability in zip(top_digits.tolist(), top_probabilities.tolist()):
        print(f"  digit {digit}: {probability:.2%}")


if __name__ == "__main__":
    main()
