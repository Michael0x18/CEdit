import java.awt.BorderLayout;
import java.awt.Desktop;
import java.awt.Font;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
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
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.plaf.nimbus.NimbusLookAndFeel;

public class Converter {
	String on_calc_name;
	String on_comp_name;
	String absolute_path;
	
	String oldtext;

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
		oldtext="";
		System.out.println("Converter window initializing");
		this.absolute_path = path;
		init();
		System.out.println("Done\nLoading data...");
		if (load_data(path)) {
			frame.dispose();
			return;
		}
		update();
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
				conditional_save();
			} else {
				save_file();
			}
		});
		Save_As.addActionListener((e) -> {
			conditional_save();
		});
		Exit.addActionListener((e) -> {
			frame.dispose();
		});

		KeyListener kl = new KeyListener() {

			@Override
			public void keyPressed(KeyEvent e) {
				return;
			}

			@Override
			public void keyReleased(KeyEvent e) {
				return;
			}

			@Override
			public void keyTyped(KeyEvent e) {
				on_calc_name = name_area.getText();
				if (e.getKeyChar() != KeyEvent.CHAR_UNDEFINED && (e.getModifiersEx() & KeyEvent.CTRL_DOWN_MASK) == 0) {
					saved = false;
					update();
					SwingUtilities.invokeLater(new Runnable() {
						public void run() {
							write_swapfile();
						}
					});
				}

			}

		};
		text.addKeyListener(kl);
		name_area.addKeyListener(kl);
	}

	private void write_swapfile() {
		System.out.println("Writing to swapfile: " + tempfile.getAbsolutePath());
		try {
			PrintWriter out = new PrintWriter(new FileWriter(tempfile));
			out.println(name_area.getText());
			for (char c : text.getText().toCharArray()) {
				out.write((int) c);
			}
			out.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
		System.out.println("Done!");
	}

	private void conditional_save() {
		JFileChooser fd = new JFileChooser();
		fd.setDialogTitle("Select file to save");
		int which = fd.showSaveDialog(frame);
		if (which == JFileChooser.APPROVE_OPTION) {
			// Set the parameters; user has selected a file!
			named = true;
			on_comp_name = fd.getSelectedFile().getName();
			absolute_path = fd.getSelectedFile().getAbsolutePath();
			//Now move the swapfile
			File f = fd.getSelectedFile();
			tempfile.renameTo(new File(f.getParent() + File.separator + "." + f.getName() + ".swp"));
			//Done!
			save_file();
		}
		update();
	}

	private void save_file() {
		// TODO save file and remove swapfile
		System.out.println("TODO: SAVE FILE");

		tempfile.delete();
		saved = true;
		update();
	}

	/**
	 * Set window title, the saved status in the title
	 */
	private void update() {
		frame.setTitle(on_comp_name + (saved ? "" : "*"));
	}

	/**
	 * Returns true if abort
	 * 
	 * @param path
	 * @return
	 */
	private boolean load_data(String path) {
		if (path == "") {
			// We were not given a file name, create a blank one
			on_comp_name = "UNTITLED.8xv";
			on_calc_name = "UNTITLED";
			name_area.setText(on_calc_name);
			File f = new File(on_comp_name);
			absolute_path = f.getAbsolutePath();
			System.out.println("new file path: " + absolute_path);
			named = false;
			saved = false;
		} else {
			// We're given a file name
			File f = new File(path);
			on_comp_name = f.getName();
			absolute_path = f.getAbsolutePath();
			String tmp = "";
			// Automatically infer oncalc name
			on_calc_name = (tmp = on_comp_name.split("\\.")[0]).substring(0, Math.min(8, tmp.length())).toUpperCase();
			named = true;
			saved = true;
		}
		File f = new File(absolute_path);
		try {
			tempfile = new File(f.getParent() + File.separator + "." + f.getName() + ".swp");
			System.out.println("Checking " + tempfile.getAbsolutePath());
			// Now check for a swapfile
			if (tempfile.exists()) {
				System.out.println("Found it");
				// Read in from swapfile
				int which = JOptionPane.showConfirmDialog(frame, "Swapfile detected. Do you want to recover it?");
				if (which == JOptionPane.YES_OPTION) {
					// Load data from swapfile
					BufferedReader br = new BufferedReader(new FileReader(tempfile));
					String name = br.readLine();
					String s = "";
					while (br.ready()) {
						s += (char) br.read();
					}
					text.setText(s);
					br.close();
					on_calc_name = name;
					on_comp_name = f.getName();
					saved = false;
					named = true;
					name_area.setText(on_calc_name);
				} else if (which == JOptionPane.NO_OPTION) {
					// Said no to recover
					tempfile.delete();
					// load from the 8xv file
					load_from_8xv();
				} else {
					// abort;
					return true;
				}
			} else {
				// If none, load from the 8xv file
				load_from_8xv();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return false;
	}

	/**
	 * Reads an 8xv file, and does setup stuff
	 */
	private void load_from_8xv() {
		saved = true;
		named = true;
		System.out.println("LOADING");
		// TODO TODO TODO TODO
		// TODO TODO TODO TODO
		// TODO TODO TODO TODO
		// TODO TODO TODO TODO
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
