import java.awt.BorderLayout;
import java.awt.Desktop;
import java.awt.Font;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URI;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.plaf.nimbus.NimbusLookAndFeel;

public class Converter {
	String on_calc_name;
	String on_comp_name;
	String absolute_path;

	JFrame frame;
	JTextArea text;

	boolean saved;
	boolean named;

	JTextArea name_area;

	// Used to store the raw text before passing through convbin
	File tempfile;

	/**
	 * Constructor. Path is "" if the file doesn't exist yet
	 * 
	 * @param path
	 */
	public Converter(String path) {
		System.out.println("Converter window initializing");
		this.absolute_path = path;
		init();
		System.out.println("Done\nLoading data...");
		if(load_data(path)) {
			frame.dispose();
			return;
		}
		System.out.println("Done");
		frame.setVisible(true);
	}

	/**
	 * Initialize GUI elements
	 */
	private void init() {
		frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		frame.setBounds(0, 0, 600, 400);
		frame.setLocationRelativeTo(null);
		frame.setLayout(new BorderLayout());
		JPanel p = new JPanel();
		p.setLayout(new BorderLayout());
		JLabel lbl = new JLabel("On-calc name:");
		name_area = new JTextArea();
		p.add(lbl, BorderLayout.WEST);
		p.add(name_area, BorderLayout.CENTER);
		frame.add(p, BorderLayout.NORTH);
		text = new JTextArea();
		text.setFont(new Font("Monospaced", Font.PLAIN, 12));
		text.setLineWrap(true);
		JScrollPane jsp = new JScrollPane(text);
		frame.add(jsp, BorderLayout.CENTER);
		JMenuBar jmb = new JMenuBar();
		JMenu File = new JMenu("File");
		JMenuItem New = new JMenuItem("New");
		JMenuItem Open = new JMenuItem("Open");
		JMenuItem Save = new JMenuItem("Save");
		JMenuItem Save_As = new JMenuItem("Save As");
		JMenuItem Exit = new JMenuItem("Exit");
		File.add(New);
		File.add(Open);
		File.add(Save);
		File.add(Save_As);
		File.add(Exit);
		jmb.add(File);
		frame.setJMenuBar(jmb);

		New.addActionListener((e) -> {
			launch_gui("");
		});
		Open.addActionListener((e) -> {
			JFileChooser fd = new JFileChooser();
			fd.setDialogTitle("Select file to open");
			int which = fd.showOpenDialog(frame);
			if (which == JFileChooser.APPROVE_OPTION) {
				File f = fd.getSelectedFile();
				launch_gui(f.getAbsolutePath());
			}
		});
		Save.addActionListener((e) -> {
			if (!named) {
				
			}
		});
		Save_As.addActionListener((e) -> {
			// TODO prompt and save
		});
		Exit.addActionListener((e) -> {
			frame.dispose();
		});
	}

	/**
	 * Set window title, the saved status in the title
	 */
	private void update() {
		frame.setTitle(on_comp_name + (saved ? "" : "*"));
	}

	/*
	 * Set up function - pulls in the
	 */
	private boolean load_data(String path) {
		if (path == "") {
			// We're starting with a blank file
			named = false;
			saved = false;
			on_calc_name = "UNTITLED";
			on_comp_name = "UNTITLED.8xp";
			path = "";// No path yet
			tempfile = new File(".UNTITLED.8xv.swp");
			name_area.setText(on_calc_name);
			update();
			return false;
		}
		File f = new File(path);
		if (f.exists()) {
			//We need to load from a file
			try {
				// First check for a swapfile
				tempfile = new File(f.getParent() + File.separator + "." + f.getName() + ".swp");
				System.out.println("Checking " + tempfile.getAbsolutePath());
				if(tempfile.exists()) {
					//Read in from swapfile
					int which = JOptionPane.showConfirmDialog(frame, "Swapfile detected. Do you want to recover it?");
					if(which==JOptionPane.YES_OPTION) {
						//Load data from swapfile
						BufferedReader br = new BufferedReader(new FileReader(tempfile));
						String name = br.readLine();
						String s="";
						while(br.ready()) {
							s+=(char)br.read();
						}
						text.setText(s);
						br.close();
						on_calc_name=name;
						on_comp_name=f.getName();
						saved=false;
						named=true;
						name_area.setText(on_calc_name);
						update();
					}else if(which==JOptionPane.NO_OPTION){
						//Said no to recover
						tempfile.delete();
						load_from_8xv();
					}else {
						//abort;
						return true;
					}
				}else {
					load_from_8xv();
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		} else {
			//A file name was passed, but it doesn't exist yet
			on_comp_name = f.getName();
			String tmp;
			//Automatically infer the on-calc name
			on_calc_name = (tmp = on_comp_name.split("\\.")[0]).substring(0, Math.min(8, tmp.length())).toUpperCase();
			saved = false;
			named = true;
			tempfile = new File("." + "on_comp_name" + ".swp");
			name_area.setText(on_calc_name);
			update();
		}
		return false;
	}

	/**
	 * Reads an 8xv file, and does setup stuff
	 */
	private void load_from_8xv() {
		saved=true;
		named=true;
		System.out.println("LOADING");
		//TODO TODO TODO TODO
		//TODO TODO TODO TODO
		//TODO TODO TODO TODO
		//TODO TODO TODO TODO
	}

	public static void launch_gui(String s) {
		Converter c = new Converter(s);
	}

	public static void main(String[] args) {
		try {
			UIManager.setLookAndFeel(new NimbusLookAndFeel());
		} catch (Exception e1) {
			e1.printStackTrace();
		}
//		try {
//			System.out.println("Testing convbin");
//			Process p = Runtime.getRuntime().exec("convbin");
//			System.out.println("Testing done");
//		} catch (IOException e) {
//			int which = JOptionPane.showConfirmDialog(null,
//					"This program requires convbin to run. Install it?\nNote: if you have it installed, make sure it is on the system path, e.g. in /usr/bin");
//			if (which == 0) {
//				try {
//					Desktop.getDesktop().browse(new URI("https://github.com/mateoconlechuga/convbin/releases"));
//				} catch (Exception e2) {
//					e2.printStackTrace();
//				}
//			}
//			return;
//		}
		if (args.length == 0) {
			System.out.println("Launching");
			launch_gui("");
		} else {
			launch_gui(args[0]);
		}
	}
}
