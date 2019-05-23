package life_game;

import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JPanel;

public class Draw_Cell extends JPanel{
	private Process_Cell pro=new Process_Cell();
	boolean flag[][];
	int size;
	public Draw_Cell(boolean flag2[][],int size2) {
		flag=flag2;
		size=size2;
	}
	
	public void paint(Graphics g){
		super.paint(g); 
	    g.drawRect(10, 10, 30*size, 30*size);
	    pro.init_1(flag, size);
		for(int i=0;i<size;i++) {
			for(int j=0;j<size;j++) {
				if(flag[i][j]) {
					g.setColor(Color.BLACK);
					g.fillRect(i*30+10,j*30+10,30,30);  
				}
				else {
					g.setColor(Color.red);
					g.fillRect(i*30+10,j*30+10,30,30);  
				}
			}
		}
		
		g.setColor(Color.BLACK);
		for(int i=1;i<=size;i++) {
	    	int y1=10+30*i,x1=10,x2=10+30*size,y2=y1;
	    	g.drawLine(x1, y1, x2, y2);
	    	
	    }
	    for(int i=1;i<=size;i++) {
	    	int x1=10+30*i,y1=10,y2=10+30*size,x2=x1;
	    	g.drawLine(x1, y1, x2, y2);
	    	
	    }
	    pro.Process(flag, size);
	}
 }