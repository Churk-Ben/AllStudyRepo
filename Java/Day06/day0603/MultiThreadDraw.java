
//MultiThreadDraw.java
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MultiThreadDraw extends JFrame {
    int x, y;

    public MultiThreadDraw() {
        this.setTitle("线程演示 202483290476 张正珂");
        Container c = this.getContentPane();
        JLabel L = new JLabel("点击可以画线哟", JLabel.CENTER);
        c.add(L, BorderLayout.CENTER);
        JButton b = new JButton("试试按我");
        b.setBorder(BorderFactory.createLineBorder(Color.blue, 5));
        // 为按钮创建边框
        c.add(b, BorderLayout.SOUTH);
        L.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) { // 在标签上按鼠标时触发
                x = e.getX(); // 获得按点的横坐标
                y = e.getY(); // 获得按点的纵坐标
                repaint(); // 重绘组件
            }
        });
        b.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                new newThread().start();
            }
        });
        this.setSize(300, 400);
        this.setVisible(true); // 显示
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    @Override
    public void paint(Graphics g) {
        g.drawLine(0, 0, x, y);
    }

    public static void main(String[] args) {
        new MultiThreadDraw();
    }

    class newThread extends Thread {
        @Override
        public void run() {
            while (true) {
            }
        }
    }
}
