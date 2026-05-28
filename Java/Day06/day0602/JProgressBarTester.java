
//JProgressBarTester.java
import javax.swing.*;
import java.awt.*;
import javax.swing.event.*;
import java.awt.event.*;

public class JProgressBarTester implements ChangeListener {
    JLabel label;
    JProgressBar pb;

    public JProgressBarTester() {
        int value = 0;
        JFrame f = new JFrame("第一类原子组件演示 202483290476 张正珂");
        Container contentPane = f.getContentPane();
        label = new JLabel("", JLabel.CENTER);
        label.setToolTipText("显示进度信息");
        pb = new JProgressBar();
        pb.setOrientation(JProgressBar.HORIZONTAL); // 设置进度条方向
        pb.setMinimum(0); // 设置最小值
        pb.setMaximum(100); // 设置最大值
        pb.setValue(value); // 初值
        pb.setStringPainted(true); // 设置进度条上显示进度
        pb.addChangeListener(this); // 增加时间监听器
        pb.setToolTipText("进度条"); // 设置提示信息
        contentPane.add(pb, BorderLayout.CENTER);
        contentPane.add(label, BorderLayout.SOUTH);
        f.setSize(400, 60);
        f.setVisible(true);
        f.addWindowListener(new WindowAdapter() { // 为窗口操作添加监听器
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });
        for (int i = 1; i <= 1000000000; i++) {
            if (i % 10000000 == 0) {
                pb.setValue(++value); // 改变进度条的值，触发ChangeEvent
            }
        }
    }

    public static void main(String[] args) {
        new JProgressBarTester();
    }

    public void stateChanged(ChangeEvent e) {
        int value = pb.getValue();
        label.setText("目前已完成进度：" + value + "%");
    }
}
