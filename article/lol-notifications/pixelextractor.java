import java.awt.Image;
import java.awt.image.ImageObserver;
import java.awt.image.PixelGrabber;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class Main {
	public static void main(String args[]) {
		Image img = null;
		try {
		    img = ImageIO.read(new File("lol/black.png"));
		} catch (IOException e) {
		    e.printStackTrace();
		}
		
		System.out.println(lolimage(img));		
	}
	
	public static String lolimage(Image img) {
		int w = img.getWidth(null);
		int h = img.getHeight(null);
		int[] pixels = new int[w * h];
		PixelGrabber pg = new PixelGrabber(img, 0, 0, w, h, pixels, 0, w);
		
		try {
		    pg.grabPixels();
		} catch (Exception e) { System.err.println("Error"); return ""; }
		
		String result = "byte myImage[" + (w * h) + "] = {\n   ";
		int max = 8;		
		
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				int v = (pixels[w * y + x] >> 16) & 0xff;
				result += Math.abs(v) % 256 * max / 256;
				if (x < w-1 || y < h-1) result += ", ";				
			}
			if (y < h-1) result += "\n   ";
		}
		
		result += "};";
		
		return result;
	}
	
	public String povtext(Image img) {
		int w = img.getWidth(null);
		int h = img.getHeight(null);
		int[] pixels = new int[w * h];
		PixelGrabber pg = new PixelGrabber(img, 0, 0, w, h, pixels, 0, w);
		try {
		    pg.grabPixels();
		} catch (Exception e) { System.err.println("Error"); return ""; }
			
		System.out.println("int length = " + w + ";");
		System.out.println("int prog[] = {");
		
		String result = "";
		
		for (int x = 0; x < w; x++) {
			String s = "0b";
			for (int y = 0; y < h; y++) {
				if (pixels[w * y + x] == -1) s += "0";
				if (pixels[w * y + x] == -16777216) s += "1";
			}
			result += "   " + s + (x == w-1 ? "\n}" : ",");
		}
		
		return result;
	}
}
