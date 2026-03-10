from PySide6.QtCore import QThread, QObject, Signal, Slot

class Worker(QObject):
    def __init__(self):
        super().__init__()
        self._running = True
        self._paused = False

    def run(self):
        while self._running:
            if not self._paused:
                # 这里放置你的工作代码
                print("线程正在运行")
            else:
                print("线程暂停中")

    def pause(self):
        self._paused = True

    def resume(self):
        self._paused = False

    def stop(self):
        self._running = False

# 创建线程
thread = QThread()
worker = Worker()
worker.moveToThread(thread)
thread.started.connect(worker.run)

# 开始线程
thread.start()
