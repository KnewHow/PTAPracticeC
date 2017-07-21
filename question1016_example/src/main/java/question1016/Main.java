package question1016;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Scanner;
import java.util.TreeMap;

/**
 * 
 * @author ygh Jul 19, 2017
 */
public class Main {
	public static final List<Integer> toll = new ArrayList<>();
	public static final int tollLength = 24;
	public static Map<String, User> userMap = new TreeMap<>(new Comparator<String>() {

		@Override
		public int compare(String o1, String o2) {
			return o1.compareTo(o2);
		}

	});
	public static final String OFF_LINE = "off-line";
	public static final String ON_LINE = "on-line";
	public static int thisMonth;

	public static int day_merge;

	public static final int TRANSFORM = 24 * 60;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		getToll(sc);
		int records = sc.nextInt();
		sc.nextLine();
		getRecores(records, sc);
		sc.close();
		sortMinutes();
		getDayCharges();
		calculateCharges();

	}

	public static void getToll(Scanner sc) {
		for (int i = 0; i < tollLength; i++) {
			int value = sc.nextInt();
			toll.add(value);
		}
	}

	public static void getRecores(int records, Scanner sc) {
		for (int i = 0; i < records; i++) {
			String line = sc.nextLine();
			String[] strs = line.split(" ");
			String username = strs[0];
			User user = null;
			if (userMap.containsKey(strs[0])) {
				user = userMap.get(strs[0]);
			} else {
				user = new User(strs[0]);
				user.setUsername(username);
			}
			int total_mins = transformString2Minutes(strs[1]);
			if (strs[2].equals(ON_LINE)) {
				user.getOn_line().add(total_mins);
			} else {
				user.getOff_list().add(total_mins);
			}
			userMap.put(username, user);
		}
	}

	public static int transformString2Minutes(String str) {
		String strs[] = str.split(":");
		int month = Integer.parseInt(strs[0]);
		int day = Integer.parseInt(strs[1]);
		int hour = Integer.parseInt(strs[2]);
		int minute = Integer.parseInt(strs[3]);
		thisMonth = month;
		int total_minutes = day * TRANSFORM + hour * 60 + minute;
		return total_minutes;
	}

	public static void sortMinutes() {
		for (Entry<String, User> entry : userMap.entrySet()) {
			User user = entry.getValue();
			if (user.getOn_line().size() != 0) {
				Collections.sort(user.getOn_line());
			}
			if (user.getOff_list().size() != 0) {
				Collections.sort(user.getOff_list());
			}
		}
	}

	public static void calculateCharges() {
		for (Entry<String, User> entry : userMap.entrySet()) {
			User user = entry.getValue();
			calculateCharges(entry.getKey(), user.getOn_line(), user.getOff_list());
			// if (user.getOn_line().size() == 0 || user.getOff_list().size() ==
			// 0) {
			// continue;
			// } else {
			// }
		}
	}

	public static void calculateCharges(String name, List<Integer> on_line, List<Integer> off_line) {
		int length = Math.min(on_line.size(), off_line.size());
		if (on_line.size() > off_line.size()) {
			int on_size = on_line.size();
			int off_size = off_line.size();
			for (int i = 0; i < on_size - off_size; i++) {
				on_line.remove(i);
			}
		}
		if (on_line.size() < off_line.size()) {
			int on_size = on_line.size();
			int off_size = off_line.size();
			for (int i = 0; i < off_size - on_size; i++) {
				off_line.remove(i);
			}
		}
		double sum_charges = 0.0;
		System.out.print(name + " ");
		System.out.println(String.format("%02d", thisMonth));
		for (int i = 0; i < length; i++) {
			List<Integer> start = calculateCharges(on_line.get(i));
			List<Integer> end = calculateCharges(off_line.get(i));
			double current = (end.get(3) - start.get(3)) / 100.0;
			sum_charges = sum_charges + current;
			System.out.print(String.format("%02d", start.get(0)) + ":" + String.format("%02d", start.get(1)) + ":"
					+ String.format("%02d", start.get(2)));
			System.out.print(" ");
			System.out.print(String.format("%02d", end.get(0)) + ":" + String.format("%02d", end.get(1)) + ":"
					+ String.format("%02d", end.get(2)));
			System.out.print(" ");
			System.out.print(String.format("%02d", off_line.get(i) - on_line.get(i)));
			System.out.print(" ");
			System.out.print("$" + String.format("%.2f", current));
			System.out.println();
		}
		System.out.print("Total amount: ");
		System.out.println("$" + String.format("%.2f", sum_charges));
	}

	public static List<Integer> calculateCharges(int total_minutes) {
		int day = total_minutes / (TRANSFORM);
		int hour = (total_minutes - day * TRANSFORM) / 60;
		int min = total_minutes % 60;
		int total = day * day_merge + min * toll.get(hour);
		for (int i = 0; i < hour; i++) {
			total = total + 60 * toll.get(i);
		}
		List<Integer> list = new ArrayList<>();
		list.add(day);
		list.add(hour);
		list.add(min);
		list.add(total);
		return list;
	}

	public static void getDayCharges() {
		int sum = 0;
		for (Integer i : toll) {
			sum = sum + i * 60;
		}
		day_merge = sum;
	}

}

class User {
	private String username;

	private List<Integer> on_line = new ArrayList<>();

	private List<Integer> off_list = new ArrayList<>();

	int sumCharges;

	public User(String username) {
		this.username = username;
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public List<Integer> getOn_line() {
		return on_line;
	}

	public void setOn_line(List<Integer> on_line) {
		this.on_line = on_line;
	}

	public List<Integer> getOff_list() {
		return off_list;
	}

	public void setOff_list(List<Integer> off_list) {
		this.off_list = off_list;
	}

	public int getSumCharges() {
		return sumCharges;
	}

	public void setSumCharges(int sumCharges) {
		this.sumCharges = sumCharges;
	}

	@Override
	public String toString() {
		return "User [username=" + username + ", on_line=" + on_line + ", off_list=" + off_list + ", sumCharges="
				+ sumCharges + "]";
	}

}
