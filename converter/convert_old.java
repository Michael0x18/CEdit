import javax.swing.JFileChooser;

import java.awt.BorderLayout;
import java.awt.Font;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JMenuBar;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;

import java.io.File;

//A converter for CEDIT and text files
public class convert_old {
	//File name
	String title;
	//Absolute path of the file. Empty if uninitialized
	String path;
	
	JFrame frame;
	JTextArea text;
	JScrollPane jsp;
	JMenuBar jmb;
	JMenu File;
	JMenuItem New;
	JMenuItem Open;
	JMenuItem Save;
	JMenuItem SaveAs;
	JMenuItem Close;
	boolean saved;
	boolean named;
	JPanel p;
	JTextArea oncalc;

	public convert_old(String path) {
		named=true;
		saved=true;
		path=new File(path).getAbsolutePath();
		title=new File(path).getName();
		if(!title.endsWith(".8xv")) {
			title+=".8xv";
			path+=".8xv";
		}
		init();
	}

	public convert_old() {
		title = "UNTITLED.8xv";
		named=false;
		saved=false;
		path="";
		init();
	}

	private void init() {
		frame = new JFrame(title +(saved?"":"*"));
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		frame.setBounds(0, 0, 600, 400);
		frame.setLocationRelativeTo(null);
		frame.setLayout(new BorderLayout());
		p = new JPanel();
		p.setLayout(new BorderLayout());
		JLabel lbl = new JLabel("On-calc name:");
		oncalc = new JTextArea();
		oncalc.setText(path);
		p.add(lbl, BorderLayout.WEST);
		frame.add(p,BorderLayout.NORTH);
		text = new JTextArea();
		text.setFont(new Font("Monospaced", Font.PLAIN, 12));
		jsp = new JScrollPane(text);
		jmb = new JMenuBar();
		File = new JMenu("File");
		New = new JMenuItem("New");
		Open = new JMenuItem("Open");
		Save = new JMenuItem("Save");
		SaveAs = new JMenuItem("Save As");
		Close = new JMenuItem("Exit");
		File.add(New);
		File.add(Open);
		File.add(Save);
		File.add(SaveAs);
		File.add(Close);
		jmb.add(File);
		frame.setJMenuBar(jmb);
		New.addActionListener((e) -> {
			launch_gui();
		});
		Open.addActionListener((e) -> {
			JFileChooser fd = new JFileChooser();
			fd.setDialogTitle("Select file to open");
			int which = fd.showOpenDialog(frame);
			if(which==JFileChooser.APPROVE_OPTION) {
				File f = fd.getSelectedFile();
				launch_gui(f.getAbsolutePath());
			}
		});
		Save.addActionListener((e) -> {
			if(!named) {
				
			}
		});
		SaveAs.addActionListener((e) -> {
			// TODO prompt and save
		});
		Close.addActionListener((e) -> {
			frame.dispose();
		});
		frame.add(jsp);
	}

	public static void launch_gui() {
		convert_old c = new convert_old();
		c.frame.setVisible(true);
	}

	public static void launch_gui(String s) {
		convert_old c = new convert_old(s);
		c.frame.setVisible(true);
	}

	public static void main(String[] args) {
		if (args.length == 0) {
			launch_gui();
		} else {
			launch_gui(args[0]);
		}
	}
}
