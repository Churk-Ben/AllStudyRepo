import os
import pyotp
import qrcode
import time
from cryptography.fernet import Fernet
from dotenv import load_dotenv


def setup_environment():
    """初始化环境：加载或生成 Master Key"""
    # 加载现有环境变量
    load_dotenv()

    master_key = os.getenv("TOTP_MASTER_KEY")

    if not master_key:
        print("⚠️  未检测到 TOTP_MASTER_KEY，正在生成...")
        # 生成一个新的 Fernet 密钥
        key = Fernet.generate_key()
        master_key = key.decode()

        # 将其写入 .env 文件
        with open(".env", "a", encoding="utf-8") as f:
            # 确保在新的一行写入
            f.write(f"\nTOTP_MASTER_KEY={master_key}\n")

        print(f"✅ 新的 Master Key 已保存到 .env 文件。")
    else:
        print("✅ 已从环境加载 Master Key。")

    return master_key


def encrypt_secret(cipher, plain_secret: str) -> bytes:
    """加密 TOTP Secret"""
    return cipher.encrypt(plain_secret.encode())


def decrypt_secret(cipher, encrypted_secret: bytes) -> str:
    """解密 TOTP Secret"""
    return cipher.decrypt(encrypted_secret).decode()


def display_qr_code(uri):
    """在终端生成并显示二维码"""
    qr = qrcode.QRCode()
    qr.add_data(uri)
    qr.make(fit=True)
    print("\n请使用 Google Authenticator / Microsoft Authenticator 扫描下方二维码：")
    # invert=True 通常在深色背景终端显示效果更好
    qr.print_ascii(invert=True)


def main():
    print("--- TOTP 真实交互验证示例 ---\n")

    # 1. 初始化环境和加密器
    master_key = setup_environment()
    cipher = Fernet(master_key.encode())

    # 2. 用户注册流程
    username = "alice@example.com"
    print(f"\n[注册流程] 为用户 {username} 生成密钥...")

    # 生成随机的 Base32 密钥 (标准 TOTP Secret)
    raw_secret = pyotp.random_base32()
    # print(f"  (调试) 原始 Secret: {raw_secret}")

    # 生成 Provisioning URI
    provisioning_uri = pyotp.totp.TOTP(raw_secret).provisioning_uri(
        name=username, issuer_name="MyPythonApp"
    )

    # 显示二维码供用户扫描
    display_qr_code(provisioning_uri)

    # 加密存储
    encrypted_secret = encrypt_secret(cipher, raw_secret)
    print(f"✅ Secret 已加密并存储。")

    print("\n" + "=" * 50)
    print("现在请在您的手机 App 上查看验证码")
    print("=" * 50 + "\n")

    # 3. 用户登录验证流程
    # 假设从数据库读取到了 encrypted_secret
    stored_data = encrypted_secret

    # 解密
    try:
        decrypted_secret = decrypt_secret(cipher, stored_data)
    except Exception as e:
        print(f"❌ 解密失败: {e}")
        return

    # 初始化 TOTP 对象
    totp = pyotp.TOTP(decrypted_secret)

    # 设置窗口容差
    # valid_window=1 表示允许当前时间步的前后各 1 个时间步 (通常是 30秒)
    # 即：允许验证 30秒前~30秒后的验证码
    window_tolerance = 1
    print(f"\n当前验证容差 (valid_window): {window_tolerance}")
    print("提示: 您可以尝试输入刚刚过期(30秒内)的验证码来测试容差。")

    # 循环验证
    while True:
        user_input = input("\n请输入您 App 上的 6 位验证码 (输入 q 退出): ").strip()

        if user_input.lower() == "q":
            print("退出程序。")
            break

        if not user_input.isdigit() or len(user_input) != 6:
            print("⚠️  格式错误，请输入 6 位数字。")
            continue

        # 验证时带上容差参数
        if totp.verify(user_input, valid_window=window_tolerance):
            print(f"✅ 验证成功! [当前时间: {time.strftime('%H:%M:%S')}]")
            print("   (您可以继续输入下一个验证码进行测试)")
        else:
            print(f"❌ 验证失败! [当前时间: {time.strftime('%H:%M:%S')}]")


if __name__ == "__main__":
    main()
