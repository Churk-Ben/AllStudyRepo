# PyTorch 手写数字识别入门

这是一个适合深度学习初学者的 MNIST 手写数字识别项目。模型使用两个卷积层提取图像特征，再通过全连接层判断图片中的数字是 `0` 到 `9` 中的哪一个。

## 项目结构

```text
.
|-- model.py          # CNN 模型结构
|-- train.py          # 下载 MNIST、训练、测试并保存模型
|-- predict.py        # 识别 MNIST 样本或自己的图片
|-- check_gpu.py      # 检查 PyTorch GPU 环境
|-- test_model.py     # 模型结构测试
|-- pyproject.toml    # 项目依赖和 cu129/国内镜像配置
`-- uv.lock           # uv 锁定的精确依赖版本
```

## 环境

当前配置使用：

- Python 3.13
- PyTorch 2.8.0 + CUDA 12.9
- torchvision 0.23.0 + CUDA 12.9
- 清华 PyPI 镜像下载普通依赖
- PyTorch 官方 CUDA 12.9 仓库下载 GPU 包

NVIDIA 驱动只需兼容 CUDA 12.9，不要求单独安装 CUDA Toolkit。PyTorch wheel 已经自带运行时。

## 1. 激活环境

首次克隆项目后，使用 uv 创建并同步环境：

```powershell
uv sync
```

推荐直接通过 `uv run` 执行命令，无需手动激活虚拟环境：

```powershell
uv run python check_gpu.py
```

如果希望激活环境，PowerShell 命令为：

```powershell
.\.venv\Scripts\Activate.ps1
```

如果 PowerShell 禁止执行激活脚本，也可以不激活，直接将后续命令中的 `python` 换成 `.\.venv\Scripts\python.exe`。

检查 GPU：

```powershell
uv run python check_gpu.py
```

输出中应看到 `CUDA available: True`、显卡名称和 `GPU calculation succeeded`。

## 2. 训练模型

```powershell
uv run python train.py
```

脚本会自动下载 MNIST。默认训练 5 轮，并将测试集准确率最高的模型保存到 `checkpoints/mnist_cnn.pt`。正常情况下准确率可达到约 98% 到 99%。

可以修改训练参数：

```powershell
uv run python train.py --epochs 10 --batch-size 256 --learning-rate 0.001
```

首次学习时建议观察每轮输出：

- `loss` 表示预测与正确答案之间的误差，通常越小越好。
- `accuracy` 表示预测正确的比例，通常越大越好。
- `train` 是模型看过的训练集结果。
- `test` 是模型没有参与学习的测试集结果，更能体现泛化能力。

## 3. 进行预测

先识别一张 MNIST 测试图片：

```powershell
uv run python predict.py --index 10
```

识别自己的图片：

```powershell
uv run python predict.py --image path\to\digit.png
```

自己的图片最好满足以下条件：只包含一个数字、数字位于中央、背景干净、数字与背景对比明显。脚本会缩放为 `28 x 28`，并自动将常见的“白底黑字”转换为 MNIST 的“黑底白字”。

## CNN 中的数据变化

输入张量形状为 `[批量大小, 1, 28, 28]`：

```text
1 x 28 x 28
  -> 卷积 + ReLU + 池化
32 x 14 x 14
  -> 卷积 + ReLU + 池化
64 x 7 x 7
  -> 展平 + 全连接层
10 个分类分数
```

训练的核心过程是：前向计算得到预测，交叉熵计算误差，`backward()` 反向传播梯度，Adam 优化器更新参数。

## 常用命令

```powershell
# 快速运行少量数据，检查整个训练流程
uv run python train.py --epochs 1 --max-train-samples 512 --max-test-samples 256

# 强制使用 CPU
uv run python train.py --cpu

# 运行模型结构测试
uv run python -m unittest -v
```
