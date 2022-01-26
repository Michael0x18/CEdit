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

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

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

	public Converter(String path) {
		this.absolute_path = path;
		init();
		load_data(path);
	}

	/**
	 * Initialize GUI
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
		JScrollPane jsp = new JScrollPane(text);
		frame.add(jsp, BorderLayout.CENTER);
	}

	/**
	 * Set window title, the saved status in the title, and the on-calc name
	 */
	private void update() {
		name_area.setText(on_calc_name);
		frame.setTitle(on_comp_name + (saved ? "" : "*"));
	}

	private void load_data(String path) {
		if (path == "") {
			// We're starting with a blank file
			named = false;
			saved = false;
			on_calc_name = "UNTITLED";
			on_comp_name = "UNTITLED.8xp";
			path = "";// No path yet
			update();
			return;
		}
		File f = new File(path);
		if (f.exists()) {
			
		} else {
			on_comp_name = f.getName();
			String tmp;
			on_calc_name = (tmp = on_comp_name.split("\\.")[0]).substring(0, Math.min(8, tmp.length())).toUpperCase();
			saved = false;
			named = true;
			update();
		}

	}

	public static void launch_gui(String s) {
		Converter c = new Converter(s);
		c.frame.setVisible(true);
	}

	public static void main(String[] args) {
		try {
			Process p = Runtime.getRuntime().exec("convbin");
		} catch (IOException e) {
			int which = JOptionPane.showConfirmDialog(null, "This program requires convbin to run. Install it?\nNote: if you have it installed, make sure it is on the system path, e.g. in /usr/bin");
			if (which == 0) {
				try {
					Desktop.getDesktop().browse(new URI("https://github.com/mateoconlechuga/convbin/releases"));
				} catch (Exception e2) {
					e2.printStackTrace();
				}
			}
			return;
		}
		if (args.length == 0) {
			launch_gui("");
		} else {
			launch_gui(args[0]);
		}
	}
}
