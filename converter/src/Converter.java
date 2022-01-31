import java.awt.BorderLayout;
import java.awt.Desktop;
import java.awt.Font;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
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
		oldtext = "";
		System.out.println("Converter window initializing...");
		this.absolute_path = path;
		init();
		System.out.println("Loading data...");
		if (load_data(path)) {
			System.out.println("Aborted, cleaning up...");
			frame.dispose();
			return;
		}
		update();
		System.out.println("Finished editor setup.");
		frame.setVisible(true);
	}

	/**
	 * Initialize GUI elements
	 */
	private void init() {
		System.out.println("Generating GUI elements...");
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
		System.out.println("Attempting to find font \"Monospaced\"");
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
		System.out.println("Setting up event drivers...");
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
		System.out.println("Finished init!");
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
		try {
			JFileChooser fd = new JFileChooser();
			fd.setDialogTitle("Select file to save");
			int which = fd.showSaveDialog(frame);
			if (which == JFileChooser.APPROVE_OPTION) {
				// Set the parameters; user has selected a file!
				named = true;
				File f = new File(
						fd.getSelectedFile().getAbsolutePath().endsWith(".8xv") ? fd.getSelectedFile().getAbsolutePath()
								: fd.getSelectedFile().getAbsolutePath() + ".8xv");
				on_comp_name = f.getName();
				absolute_path = f.getAbsolutePath();
				// Now move the swapfile
				File tempfile_new = new File(f.getParent() + File.separator + "." + f.getName() + ".swp");
				if (tempfile.exists()) {
					BufferedReader br = new BufferedReader(new FileReader(tempfile));
					PrintWriter out = new PrintWriter(new FileWriter(tempfile_new));
					while (br.ready()) {
						out.print((char) br.read());
					}
					br.close();
					out.close();
					tempfile.delete();
				}
				tempfile = tempfile_new;
				// Done!
				save_file();
			}
			update();
		} catch (Exception e) {
			e.printStackTrace();
		}
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
			System.out.println("No path given, use default: ./Untitled.8xv");
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
			System.out.println("Given filename:" + absolute_path);
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
			System.out.println("Initializing swapfile...");
			tempfile = new File(f.getParent() + File.separator + "." + f.getName() + ".swp");
			System.out.println("Checking " + tempfile.getAbsolutePath());
			// Now check for a swapfile
			if (tempfile.exists()) {
				System.out.println("Swapfile found, prompting user...");
				// Read in from swapfile
				int which = JOptionPane.showConfirmDialog(frame, "Swapfile detected. Do you want to recover it?");
				if (which == JOptionPane.YES_OPTION) {
					// Load data from swapfile
					System.out.println("User selected: yes");
					System.out.println("Recover from swapfile");
					on_comp_name = f.getName();
					load_swapfile();
				} else if (which == JOptionPane.NO_OPTION) {
					System.out.println("User selected: no");
					System.out.println("Deleting swapfile...");
					// Said no to recover
					tempfile.delete();
					// load from the 8xv file
					System.out.println("Attempting to load data from 8xv file");
					load_from_8xv();
				} else {
					// abort;
					System.out.println("User selected option: cancel");
					return true;
				}
			} else {
				// If none, load from the 8xv file
				System.out.println("No swapfile detected, attempting to load from 8xv");
				load_from_8xv();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return false;
	}

	private void load_swapfile() throws IOException {
		BufferedReader br = new BufferedReader(new FileReader(tempfile));
		String name = br.readLine();
		String s = "";
		while (br.ready()) {
			s += (char) br.read();
		}
		text.setText(s);
		br.close();
		on_calc_name = name;
		saved = false;
		named = true;
		name_area.setText(on_calc_name);
	}

	/**
	 * Reads an 8xv file, and does setup stuff
	 */
	private void load_from_8xv() {
		saved = true;
		named = true;
		System.out.println("Checking if 8xv file exists...");
		File f = new File(absolute_path);
		if (f.exists()) {
			System.out.println("Found 8xv file, opening and decoding...");
			System.out.println("Running calc2txt from file: " + absolute_path + " to " + tempfile.getAbsolutePath());
			calc2text(f, tempfile);
			try {
				if (tempfile.exists()) {
					load_swapfile();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
			System.out.println("Swapfile loaded");
		} else {
			System.out.println("No 8xv file found, exiting subroutine...");
		}

	}

	public static void launch_gui(String s) {
		Converter c = new Converter(s);
	}

	public static void main(String[] args) {// \u0001 ree
		try {
			UIManager.setLookAndFeel(new NimbusLookAndFeel());
		} catch (Exception e1) {
			e1.printStackTrace();
		}
		if (args.length == 0) {
			System.out.println("Launching");
			launch_gui("");
		} else {
			launch_gui(args[0]);
		}
	}

	public static void calc2text(File calcfile, File compfile) {
		try {
			BufferedInputStream fis = new BufferedInputStream(new FileInputStream(calcfile));
			for(int i = 0; i < 53; i++) {
				fis.read();//Get rid of the **TI83F* header and the {26 10 00} and the comment
			}
			int b = fis.read();
			int a = fis.read();
			a<<=8;
			a|=b;
			for(int i = 0; i < a; i++) {
				
			}
			
			
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	public static void text2calc(File compfile, File calcfile) {

	}

}
