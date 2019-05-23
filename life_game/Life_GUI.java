package life_game;

import java.awt.Button;
import java.awt.Color;

import javax.swing.JFrame;

public class Life_GUI extends JFrame{
	private int size=21;
	private boolean flag[][]=new boolean[size][size];
	public Life_GUI(){
		this.setSize(800, 800);
		this.setLocation(200, 200);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		
	}
	public void game_start() throws InterruptedException {
		
		while(true) {
			Draw_Cell mp=new Draw_Cell(flag,size);
//			Button but=new Button();
//			but.setLocation(980, 980);
//			but.setSize(100, 100);
//			but.setBounds(980, 980, 1000, 1000);
//			but.setName("¿ªÊ¼");
//			but.setBackground(Color.blue);
//			mp.add(but);
			
			this.add(mp);
			this.setVisible(true);
			Thread.sleep(600);
			mp.isDisplayable();
		}
	}
}