/**
 * Ashley Madison
 * RSS Feed Generator experimenting with UI using Java swing. 
 * May 2019
 */

package practiceProgs;
import java.net.URL;
import java.io.*;
import java.util.*;
import com.sun.syndication.io.*;
import com.sun.syndication.feed.synd.*;
import javax.swing.*;
import java.awt.*;
import javax.swing.text.html.*;
import java.awt.event.*;
import java.awt.datatransfer.*;

public class RSSFeed implements ActionListener{
	JFrame frame; JLabel label1, titleLabel, linkLabel, descLabel;
	JPanel panel, card1, card2;
	JButton button, button2, button3;
	JTextField title, link, desc, title2, link2, desc2;
	SyndFeed feed = new SyndFeedImpl();
	ArrayList entries = new ArrayList();
	SyndEntry entry;
	SyndContent descript;
	
	public void readRSS(){
		final String CARD1P = "card 1 boi";
		final String CARD2P = "card 2 boi";
		frame = new JFrame("RSS Feed Generator");
		
		label1 = new JLabel("Feed Data Aquired!");
		titleLabel = new JLabel("Input Title Below: ");
		linkLabel = new JLabel("Input Link Below: ");
		descLabel = new JLabel("Input Description Below: ");

		title = new JTextField("");
		title.setMaximumSize(new Dimension(1000,20));
		link = new JTextField("");
		link.setMaximumSize(new Dimension(1000,20));
		desc = new JTextField("");
		desc.setMaximumSize(new Dimension(1000,20));
		
		title2 = new JTextField("Input title here: ");
		title2.setMaximumSize(new Dimension(1000,20));
		link2 = new JTextField("Input link here: ");
		link2.setMaximumSize(new Dimension(1000,20));
		desc2 = new JTextField("Input description here: ");
		desc2.setMaximumSize(new Dimension(1000,20));
		
		button = new JButton("INPUT");
		button.addActionListener(this);
		button2 = new JButton("Input Another");
		button2.addActionListener(this);
		button3 = new JButton("Finish and read to file");
		button3.addActionListener(this);
	
		card1 = new JPanel();
		card2 = new JPanel();
		panel = new JPanel(new CardLayout());
		
		card1.setLayout(new BoxLayout(card1, BoxLayout.Y_AXIS));
		card2.setLayout(new BoxLayout(card2, BoxLayout.Y_AXIS));
		
		card1.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		panel.add(card1, CARD1P);
		card1.add(Box.createRigidArea(new Dimension(10,10)));
		card1.add(titleLabel);
		card1.add(title);
		card1.add(Box.createRigidArea(new Dimension(10,10)));
		card1.add(linkLabel);
		card1.add(link);
		card1.add(Box.createRigidArea(new Dimension(10,10)));
		card1.add(descLabel);
		card1.add(desc);
		card1.add(Box.createRigidArea(new Dimension(10,10)));
		card1.add(button);
		
		card2.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		panel.add(card2, CARD2P);
		card2.add(Box.createRigidArea(new Dimension(10,10)));
		card2.add(title2);
		card2.add(Box.createRigidArea(new Dimension(10,10)));
		card2.add(link2);
		card2.add(Box.createRigidArea(new Dimension(10,10)));
		card2.add(desc2);
		card2.add(Box.createRigidArea(new Dimension(10,10)));
		card2.add(button2);
		card2.add(Box.createRigidArea(new Dimension(10,10)));
		card2.add(button3);
		card2.add(Box.createRigidArea(new Dimension(10,10)));
		card2.add(label1);
		
		frame.add(panel);
		frame.setSize(575,275);
		frame.setLayout(new CardLayout());
		frame.setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e) {
		if(e.getSource()==button) { //input feed data
			String titleText = title.getText();
			String linkText = link.getText();
			String descText = desc.getText();
			
			feed.setFeedType("rss_1.0");
			feed.setTitle(titleText);
			feed.setLink(linkText);
			feed.setDescription(descText);

			CardLayout cl = (CardLayout)(panel.getLayout());
			cl.show(panel, "card 2 boi");
		}
		if(e.getSource()==button2) { //input again
			String titleText = title2.getText();
			String linkText = link2.getText();
			String descText = desc2.getText();
			
			entry = new SyndEntryImpl(); ///create a new entry and set its contents
			entry.setTitle(titleText);
			entry.setLink(linkText);
			descript = new SyndContentImpl(); //set the entries description
			descript.setType("text/plain");
			descript.setValue(descText);
			entry.setDescription(descript);
			entries.add(entry); //add entry to arraylist
			
			title2.setText(""); link2.setText(""); desc2.setText(""); //remove info so we can add another entry or quit	
			label1.setText("Entry Data Aquired! Proceed With Next Entry!");
		}
		if(e.getSource()==button3) { //finish and input all of the rest of your info...
			String titleText = title2.getText();
			String linkText = link2.getText();
			String descText = desc2.getText();
			
			entry = new SyndEntryImpl();
			entry.setTitle(titleText);
			entry.setLink(linkText);
			descript = new SyndContentImpl();
			descript.setType("text/plain");
			descript.setValue(descText);
			entry.setDescription(descript);
			
			entries.add(entry); //add to arraylist
			feed.setEntries(entries); //add arraylist to the feed
			
			try {//write everything to a file
				JFileChooser fc = new JFileChooser();
				int smol = fc.showSaveDialog(frame);
				File f = new File(fc.getSelectedFile().getPath());
			
				Writer writer = new FileWriter(f);
				SyndFeedOutput output = new SyndFeedOutput();
				output.output(feed, writer); //Read the XML RSSFeed into a plain text file
				writer.close();
			}
			catch(Exception ex) {ex.printStackTrace();}
		}
	}
	public static void main(String[] args) {
		new RSSFeed().readRSS();
	}
	

}
