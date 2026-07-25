"""Print PyTorch and CUDA status, then run a small GPU calculation."""

import torch


def main() -> None:
    print(f"PyTorch: {torch.__version__}")
    print(f"PyTorch CUDA runtime: {torch.version.cuda}")
    print(f"CUDA available: {torch.cuda.is_available()}")

    if not torch.cuda.is_available():
        raise SystemExit("CUDA is unavailable. Check the NVIDIA driver and PyTorch build.")

    device = torch.device("cuda")
    print(f"GPU: {torch.cuda.get_device_name(0)}")
    result = torch.randn(512, 512, device=device) @ torch.randn(512, 512, device=device)
    print(f"GPU calculation succeeded: shape={tuple(result.shape)}, device={result.device}")


if __name__ == "__main__":
    main()
