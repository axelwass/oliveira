package gui;


import general.Universo;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferStrategy;
import java.nio.Buffer;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.text.Position;

public class Window extends JFrame{

	private static final long serialVersionUID = 1L;
	
	private List<Double[]> pos = new LinkedList<Double[]>();
	private List<Double[]> oldPos = new LinkedList<Double[]>();
	BufferStrategy strategy;
	double last;

	public Window(){
		super("Oliveira");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setBounds(0, 0, 1800, 1100);
		armarMenu();
		setLayout(null);
		setVisible(true);
		createBufferStrategy(2);
		strategy = getBufferStrategy();
		last  = System.currentTimeMillis() / 1000.0;
	}

	public void refresh(List<Double[]> pos){
		oldPos=this.pos;
		this.pos=pos;
		
		long t1=System.currentTimeMillis();
		while(System.currentTimeMillis()-t1<10);

		Universo.lapso = System.currentTimeMillis() / 1000.0 - last;
		last = System.currentTimeMillis() / 1000.0;
		
		//repaint();
		paint2(strategy.getDrawGraphics());
	}
	
	
	public void paint2(Graphics g){
		//this.paintComponents(g)
	   	//Graphics2D g2 = (Graphics2D)g;
		//super.paint(g2);
//	   	for(Double[] p : oldPos){
//	   		g2.clearRect((int)(p[0] * 10 + getWidth()/2) , (int)(p[1] * 10 + getHeight() / 2), 25, 25);
//	   	}
		g.setColor(Color.white);
		g.fillRect(0, 0, getWidth(), getHeight());
		g.setColor(Color.black);
		for(Double[] p : pos){
			if(p.length==1){
				
				g.drawOval((int)(getWidth()/2 + p[0]*10) , getHeight()/2, 25, 25);
			}
			if(p.length==2){
				g.drawOval((int)(getWidth()/2 + p[0]*10) , (int)(getHeight()/2 + p[1]*10), 25, 25);
			}
		}
		g.dispose();
		strategy.show();
	}






	private void armarMenu() {
		JMenuBar menuBar= new JMenuBar();
		
		
		JMenu menu=new JMenu("Archivo");
		JMenuItem item= new JMenuItem("Cerrar");
		item.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				setVisible(false);
			}
			
		});
		
		menu.add(item);
		
		
		menuBar.add(menu);
		
		
		setJMenuBar(menuBar);
		
	}


}
