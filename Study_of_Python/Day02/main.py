import requests
import time
import sys

login_url="https://examsafety.nuist.edu.cn//exam_login.php"
login_headers={"accept":"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7","accept-encoding":"gzip, deflate, br, zstd","accept-language":"zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6","cache-control":"max-age=0","connection":"keep-alive","content-length":"94","content-type":"application/x-www-form-urlencoded","host":"examsafety.nuist.edu.cn","origin":"https://examsafety.nuist.edu.cn","referer":"https://examsafety.nuist.edu.cn//index.php","sec-ch-ua":'"Chromium";v="128", "Not;A=Brand";v="24", "Microsoft Edge";v="128"',"sec-ch-ua-mobile":"?0","sec-ch-ua-platform":'"Windows"',"sec-fetch-dest":"iframe","sec-fetch-mode":"navigate","sec-fetch-site":"same-origin","sec-fetch-user":"?1","upgrade-insecure-requests":"1","user-agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/128.0.0.0 Safari/537.36 Edg/128.0.0.0"}

choose=int(input("请选择登录方式：\n1：账号密码登录\n2：cookies登录\n"))

if choose==2:
    cookie=input("请输入cookies：")

elif choose==1:
    user=input("请输入账号：")
    password=input("请输入密码：")

    login_data=f"xuehao={user}&password={password}&postflag=1&cmd=login&role=0&�ύ=��¼"

    login=requests.post(login_url,data=login_data,headers=login_headers)

    cookie = "; ".join([f"{cookie.name}={cookie.value}" for cookie in login.cookies])

else:
    print("错误")
    sys.exit(0)


headers={"accept":"*/*","accept-encoding":"gzip, deflate, br, zstd","accept-language":"zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6","connection":"keep-alive","content-length":"146","content-type":"multipart/form-data; boundary=----WebKitFormBoundarysXGwBj7L9uYnP3AM","cookie":cookie,"host":"examsafety.nuist.edu.cn","origin":"https://examsafety.nuist.edu.cn","sec-ch-ua":'"Chromium";v="128", "Not;A=Brand";v="24", "Microsoft Edge";v="128"',"sec-ch-ua-mobile":"?0","sec-ch-ua-platform":'"Windows"',"sec-fetch-dest":"empty","sec-fetch-mode":"cors","sec-fetch-site":"same-origin","user-agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/128.0.0.0 Safari/537.36 Edg/128.0.0.0","x-requested-with":"XMLHttpRequest"}
data="""------WebKitFormBoundarysXGwBj7L9uYnP3AM
Content-Disposition: form-data; name="cmd"

xuexi_online
------WebKitFormBoundarysXGwBj7L9uYnP3AM--"""
url="https://examsafety.nuist.edu.cn//exam_xuexi_online.php"


while True:
    
    r=requests.post(url,data=data,headers=headers)
    s = r.text
    s = s.encode('utf-8').decode('unicode_escape')
    print(s)
    time.sleep(60)
