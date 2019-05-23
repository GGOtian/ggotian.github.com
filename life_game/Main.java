package life_game;
public class Main{
	
	public static void main(String []args) {
		Life_GUI GUI=new Life_GUI();
		try {
			GUI.game_start();
		} catch (InterruptedException e) {
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		}
	}
}