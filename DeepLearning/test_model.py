"""Small tests that do not download MNIST."""

import unittest

import torch

from model import DigitCNN


class DigitCNNTest(unittest.TestCase):
    def test_output_shape(self):
        model = DigitCNN()
        output = model(torch.randn(4, 1, 28, 28))
        self.assertEqual(output.shape, (4, 10))


if __name__ == "__main__":
    unittest.main()
