//package practiceProgs;
import javax.swing.*;
import java.awt.event.*;
import java.awt.datatransfer.*;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.awt.*;
import javax.swing.text.html.*;


/**
 * @author Ashley Madison
 * Simple Text Editor Program
 * This program allows a user to open/save and manipulate plain text documents.
 */
public class TextEditor extends JFrame implements ActionListener{
	JEditorPane pane; JMenu menu, menu2,menu3; JMenuBar bar; 
	JMenuItem open, save, color, background,cut,copy,paste;
	
	
	
	/**
	 * Constructor with all of the information about the different components of the 
	 * JFrame and what they will do.
	 */
	TextEditor(){
	
		//The first menu 
		bar = new JMenuBar();
		menu = new JMenu("File");
		open = new JMenuItem("Open Document");
		open.addActionListener(this);
		save = new JMenuItem("Save Document");
		save.addActionListener(this);
		
		//The second menu
		menu2 = new JMenu("Colors");
		color = new JMenuItem("Change text color");
		color.addActionListener(this);
		background = new JMenuItem("Change Background color");
		background.addActionListener(this);
		
		//The third menu
		menu3 = new JMenu("Commands");
		cut = new JMenuItem("Cut");
		cut.addActionListener(this);
		copy = new JMenuItem("Copy");
		copy.addActionListener(this);
		paste = new JMenuItem("Paste");
		paste.addActionListener(this);
		
		//Adding all of the menus to the bar and the items to the menus.
		menu.add(open);menu.add(save);bar.add(menu);
		menu2.add(color);menu2.add(background);bar.add(menu2);
		menu3.add(cut);menu3.add(copy);menu3.add(paste);bar.add(menu3);
		
		//Creating instance of the text editing pane.
		pane = new JEditorPane();
		//pane.setContentType("text/plain");
		pane.setContentType("HTML/plain");
		pane.setFont(new Font("Arial", Font.PLAIN, 30));  
		
		//Detailing the JFrame
		setContentPane(pane);
		setJMenuBar(bar);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setSize(1000,1000);
		setVisible(true);
		setLayout(null);
		setTitle("Better Text Editor");
	}
	/**
	 * Method that details what each of the menu items will be doing. 
	 */
	public void actionPerformed(ActionEvent e) {
		
		if(e.getSource() == open) { //If you want to open a file
			JFileChooser fj = new JFileChooser();
			int i = fj.showOpenDialog(this);
			
			if(i == JFileChooser.APPROVE_OPTION) {
				File f = fj.getSelectedFile();
				String filepath = f.getPath();
				
				try {
					BufferedReader br = new BufferedReader(new FileReader(filepath));
					String s1 = "",s2 = "";
					
					while((s1=br.readLine())!=null) { //read each line of the file
						s2+=s1+"\n";
					}
					pane.setText(s2); //set the text area with the contents of the file
					br.close();
					
				}catch(Exception ex) {ex.printStackTrace();}
			}
		}
		
		if(e.getSource() == save) { //If you want to save a file
			JFileChooser fc = new JFileChooser();
			int smol = fc.showSaveDialog(this);
			File f = new File(fc.getSelectedFile().getPath());
			
				try {
					String source = pane.getText();
					char buffer[] = new char[source.length()]; //makes an array of chars with the length of the strings in source
					source.getChars(0, source.length(),buffer, 0); //not sure
					
					FileWriter fw = new FileWriter(f +".txt"); //makes a file writer
					
					for(int i = 0;i<buffer.length;i++) { //while i is less than the length of the char array
						fw.write(buffer[i]); 
					}
					fw.close();
				}catch(Exception ex) {ex.printStackTrace();}
		}
		if(e.getSource()==color) { //If you want to change the text color
			
			Color kallum = JColorChooser.showDialog(this, "Select a Color", Color.BLACK);
			pane.setForeground(kallum);
			
		}
		if(e.getSource()==background) { //If you want to change the background color
			Color kallum = JColorChooser.showDialog(this, "Select a Color", Color.BLACK);
			pane.setBackground(kallum);
		}
		if(e.getSource()==cut) { //If you want to cut
			pane.cut();
		}
		if(e.getSource()==copy) { //If you want to copy
			pane.copy();
		}
		if(e.getSource()==paste) { //If you want to paste
			pane.paste();
		}
	}
	/**
	 * Instantiates an instance of the SwingPlayground class.
	 * @param args
	 */
	public static void main(String[] args) {
	new TextEditor();
	}


}
