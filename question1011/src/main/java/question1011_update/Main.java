package question1011_update;

import java.beans.BeanInfo;
import java.beans.IntrospectionException;
import java.beans.Introspector;
import java.beans.PropertyDescriptor;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int totalStudent = sc.nextInt();
		int searchAmount = sc.nextInt();
		Map<String, Student> studentMap = getStudentInfo(totalStudent, sc);
		List<Student> studentList = new ArrayList<Student>();
		List<String> idList = getSearchList(searchAmount, sc);
		sc.close();
		for (Entry<String, Student> entry : studentMap.entrySet()) {
			studentList.add(entry.getValue());
		}
		// for (int i = 1; i <= 4; i++) {
		// sortByAverageScore(studentList, i);
		// setAverageRank(studentList, studentMap, i);
		// }
		// search(studentMap, idList);
		Map<Integer, PropertyDescriptor> map = getPropertyDescriptors();
		for (Entry<Integer, PropertyDescriptor> entry : map.entrySet()) {
			System.out.println(entry.getKey());
		}

	}

	public static void search(Map<String, Student> studentMap, List<String> idList) {
		for (String id : idList) {
			if (studentMap.containsKey(id)) {
				Student student = studentMap.get(id);
				student.getBestRank();
			} else {
				System.out.println("N/A");
			}
		}
	}

	/**
	 * A method to get student information from input data
	 * 
	 * @param totalStudent
	 * @param sc
	 * @return
	 */
	public static Map<String, Student> getStudentInfo(int totalStudent, Scanner sc) {
		Map<String, Student> map = new HashMap<String, Student>();
		sc.nextLine();
		for (int i = 0; i < totalStudent; i++) {
			String str = sc.nextLine();
			String[] strs = str.split(" ");
			Student student = new Student();
			student.setId(strs[0]);
			student.setCLanguageScores(Integer.parseInt(strs[1]));
			student.setMathematicsScores(Integer.parseInt(strs[2]));
			student.setEnglishScores(Integer.parseInt(strs[3]));
			map.put(student.getId(), student);
		}
		return map;
	}

	/**
	 * A method to get id search list
	 * 
	 * @param searchAmount
	 * @param sc
	 * @return
	 */
	public static List<String> getSearchList(int searchAmount, Scanner sc) {
		List<String> idList = new ArrayList<String>();
		for (int i = 0; i < searchAmount; i++) {
			String str = sc.nextLine();
			idList.add(str);
		}
		return idList;

	}

	public static void setAverageRank(List<Student> studentList, Map<String, Student> studentMap, int flag) {
		if (flag == 1) {
			studentMap.get(studentList.get(0).getId()).setAverageRank(1);
			for (int i = 1; i < studentList.size(); i++) {
				if (studentList.get(i).getAverageScore() == studentList.get(i - 1).getAverageScore()) {
					studentMap.get(studentList.get(i).getId())
							.setAverageRank(studentMap.get(studentList.get(i - 1).getId()).getAverageRank());
				} else {
					studentMap.get(studentList.get(i).getId()).setAverageRank(i + 1);
				}
			}
		} else if (flag == 2) {
			studentMap.get(studentList.get(0).getId()).setCLanguageRank(1);
			for (int i = 1; i < studentList.size(); i++) {
				if (studentList.get(i).getCLanguageScores() == studentList.get(i - 1).getCLanguageScores()) {
					studentMap.get(studentList.get(i).getId())
							.setCLanguageRank(studentMap.get(studentList.get(i - 1).getId()).getCLanguageRank());
				} else {
					studentMap.get(studentList.get(i).getId()).setCLanguageRank(i + 1);
				}
			}
		} else if (flag == 3) {
			studentMap.get(studentList.get(0).getId()).setMathematicsRank(1);
			for (int i = 1; i < studentList.size(); i++) {
				if (studentList.get(i).getMathematicsScores() == studentList.get(i - 1).getMathematicsScores()) {
					studentMap.get(studentList.get(i).getId())
							.setMathematicsRank(studentMap.get(studentList.get(i - 1).getId()).getMathematicsRank());
				} else {
					studentMap.get(studentList.get(i).getId()).setMathematicsRank(i + 1);
				}
			}
		} else if (flag == 4) {
			studentMap.get(studentList.get(0).getId()).setEnglishRank(1);
			for (int i = 1; i < studentList.size(); i++) {
				if (studentList.get(i).getEnglishScores() == studentList.get(i - 1).getEnglishScores()) {
					studentMap.get(studentList.get(i).getId())
							.setEnglishRank(studentMap.get(studentList.get(i - 1).getId()).getEnglishRank());
				} else {
					studentMap.get(studentList.get(i).getId()).setEnglishRank(i + 1);
				}
			}
		}

	}

	public static void sortByAverageScore(List<Student> students, int flag) {
		List<Student> temp = new ArrayList<Student>(students.size());
		for (int i = 0; i < students.size(); i++) {
			temp.add(null);
		}
		mergerSort(students, temp, 0, students.size() - 1, flag);
	}

	public static void mergerSort(List<Student> students, List<Student> temp, int left, int right, final int flag) {
		if (left < right) {
			int mid = (left + right) / 2;
			mergerSort(students, temp, left, mid, flag);
			mergerSort(students, temp, mid + 1, right, flag);
			merge(students, temp, left, mid, right, flag);
		}

	}

	private static void merge(List<Student> students, List<Student> temp, int left, int mid, int right, int flag) {
		int low = left;
		int high = mid + 1;
		int counter = left;
		Map<String, Integer> information = compareCatagory(students, temp, counter, low, high, mid, right, flag);
		low = information.get("low");
		high = information.get("high");
		counter = information.get("counter");
		while (low <= mid) {
			temp.set(counter++, students.get(low));
			low++;
		}
		while (high <= right) {
			temp.set(counter++, students.get(high));
			high++;
		}

		for (int i = left; i <= right; i++) {
			students.set(i, temp.get(i));
		}
	}

	private static Map<String, Integer> compareCatagory(List<Student> students, List<Student> temp, int counter,
			int low, int high, int mid, int right, int flag) {
		Map<Integer, PropertyDescriptor> propsMap = getPropertyDescriptors();
		while (low <= mid && high <= right) {

		}
		Map<String, Integer> information = new HashMap<String, Integer>();
		information.put("low", low);
		information.put("high", high);
		information.put("counter", counter);
		return information;

	}

	private static Map<Integer, PropertyDescriptor> getPropertyDescriptors() {
		BeanInfo beanInfo = null;
		Map<Integer, PropertyDescriptor> flagToPropertyDes = new HashMap<Integer, PropertyDescriptor>();
		Map<String, Integer> mapping = new HashMap<String, Integer>();
		mapping.put("averageScore", 1);
		mapping.put("CLanguageScores", 2);
		mapping.put("mathematicsScores", 3);
		mapping.put("englishScores", 4);

		try {
			beanInfo = Introspector.getBeanInfo(Student.class);
		} catch (IntrospectionException e) {
			e.printStackTrace();
		}
		PropertyDescriptor[] props = beanInfo.getPropertyDescriptors();
		for (int i = 0; i < props.length; i++) {
			PropertyDescriptor prop = props[i];
			String name = prop.getName();
			if (mapping.containsKey(name)) {
				flagToPropertyDes.put(mapping.get(name), prop);
			}
		}
		return flagToPropertyDes;

	}

}

/**
 * A student information
 * 
 * @author ygh Jun 21, 2017
 */
class Student {
	private String id;
	private Integer CLanguageScores;
	private Integer MathematicsScores;
	private Integer EnglishScores;

	private Integer CLanguageRank;
	private Integer MathematicsRank;
	private Integer EnglishRank;
	private Integer averageRank;

	public Student() {
		super();
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public Integer getCLanguageScores() {
		return CLanguageScores;
	}

	public void setCLanguageScores(Integer cLanguageScores) {
		CLanguageScores = cLanguageScores;
	}

	public Integer getMathematicsScores() {
		return MathematicsScores;
	}

	public void setMathematicsScores(Integer mathematicsScores) {
		MathematicsScores = mathematicsScores;
	}

	public Integer getEnglishScores() {
		return EnglishScores;
	}

	public void setEnglishScores(Integer englishScores) {
		EnglishScores = englishScores;
	}

	public Integer getCLanguageRank() {
		return CLanguageRank;
	}

	public void setCLanguageRank(Integer cLanguageRank) {
		CLanguageRank = cLanguageRank;
	}

	public Integer getMathematicsRank() {
		return MathematicsRank;
	}

	public void setMathematicsRank(Integer mathematicsRank) {
		MathematicsRank = mathematicsRank;
	}

	public Integer getEnglishRank() {
		return EnglishRank;
	}

	public void setEnglishRank(Integer englishRank) {
		EnglishRank = englishRank;
	}

	public Integer getAverageRank() {
		return averageRank;
	}

	public void setAverageRank(Integer averageRank) {
		this.averageRank = averageRank;
	}

	public Double getAverageScore() {
		return (double) ((this.getCLanguageScores() + this.getMathematicsScores() + this.getEnglishScores()) / 3);
	}

	public void getBestRank() {
		List<Integer> ranks = new ArrayList<Integer>();
		ranks.add(this.getAverageRank());
		ranks.add(this.getCLanguageRank());
		ranks.add(this.getMathematicsRank());
		ranks.add(this.getEnglishRank());
		int recordIndex = 0;
		int bestRank = ranks.get(0);
		for (int i = 1; i < ranks.size(); i++) {
			if (bestRank > ranks.get(i)) {
				recordIndex = i;
				bestRank = ranks.get(i);
			}
		}
		System.out.print(bestRank + " ");
		System.out.println(Mapping.map.get(recordIndex));

	}

	@Override
	public String toString() {
		return this.getId() + ":" + this.getMathematicsRank();
	}

}

class Mapping {
	public static final Map<Integer, String> map = new HashMap<Integer, String>();
	static {
		map.put(0, "A");
		map.put(1, "C");
		map.put(2, "M");
		map.put(3, "E");
	}
}
