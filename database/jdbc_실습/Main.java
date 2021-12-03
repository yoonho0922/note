import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.sql.*;
import java.util.Scanner;

public class Main {
    static Connection conn;
    static Statement stmt;
    static ResultSet rs;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        initDatabase();

        boolean run = true;
        while (run) {
            createInterface();
            int n = sc.nextInt();
            switch (n){
                case 0:
                    System.out.println("프로그램을 종료합니다.");
                    run = false;
                    break;
                case 1:
                    createTable("create_table.txt");
                    insertData("movie_data.txt");
                    break;
                case 2:
                    searchTitle();
                    break;
                case 3:
                    searchTotalNum();
                    break;
                case 4:
                    searchDate();
                    break;
                default:
                    System.out.println("0-4 중의 수를 입력해주세요.");
                    break;
            }
            System.out.println();
        }


        try {
            conn.close();
            stmt.close();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }


    }

    private static void searchDate() {
        Scanner sc = new Scanner(System.in);
        System.out.print("사용자 입력 : ");
        String str = sc.nextLine();
        String splited[] = str.split(",");
        String query = "select * from movie where releasedate>='"+splited[0]+"' and releasedate<='"+splited[1].trim()+"';";

        search(query);
    }

    private static void searchTotalNum() {
        Scanner sc = new Scanner(System.in);
        System.out.print("사용자 입력 : ");
        String str = sc.nextLine();
        String query = "select * from movie where totalnum >= "+str+";";

        search(query);
    }

    private static void searchTitle() {
        Scanner sc = new Scanner(System.in);
        System.out.print("사용자 입력 : ");
        String str = sc.nextLine();
        String query = "select * from movie where title like '%" + str +"%';";

        search(query);
    }

    private static void search(String query) {
        try {

            rs = stmt.executeQuery(query);
//            System.out.println(query);

            if (!rs.isBeforeFirst()){
                System.out.println("일치하는 정보가 없습니다.");
            }

            while(rs.next()){
                printResult();
            }
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
    }

    private static void printResult() throws SQLException {
        System.out.println(String.format("|%s|%s|%s|%s|%s|%s|%s|%s",
                rs.getString("id"),
                rs.getString("title"),
                rs.getString("company"),
                rs.getString("releasedate"),
                rs.getString("country"),
                rs.getString("totalscreen"),
                rs.getString("profit"),
                rs.getString("totalnum"),
                rs.getString("grade"))
        );
    }

    private static void createTable(String fileName) {
        try {
            BufferedReader reader = new BufferedReader(
                    new FileReader(fileName));

            String str;
            StringBuilder query = new StringBuilder();

            while ((str = reader.readLine()) != null) {
                query.append(str);
            }

            stmt.executeUpdate(String.valueOf(query));
            System.out.println("테이블이 생성되었습니다.");

        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static void insertData(String fileName) {
        try {
            rs = stmt.executeQuery("select * from movie");
            if (rs.next()) {
                System.out.println("이미 데이터가 존재합니다.");
                return;
            }

            BufferedReader reader = new BufferedReader(
                    new FileReader(fileName));

            String str;
            int cnt = 0;
            while ((str = reader.readLine()) != null) {
                String splited[] = str.split("\\|");
                String query = String.format("insert into movie values('%s', '%s', '%s', " +
                                "'%s', '%s', '%s', '%s', '%s', '%s');",
                        splited[1], splited[2], splited[3], splited[4], splited[5], splited[6], splited[7], splited[8], splited[9]);
                stmt.executeUpdate(query);
                cnt++;
            }

            System.out.println(cnt + " 개의 데이터 삽입 완료.");

        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static void createInterface() {
        String str = "========================================\n" +
                "(0) 종료\n" +
                "(1) 릴레이션 생성 및 데이터 추가\n" +
                "(2) 제목을 이용한 검색\n" +
                "(3) 관객수를 이용한 검색\n" +
                "(4) 개봉일을 이용한 검색\n" +
                "========================================\n" +
                "원하는 번호를 입력 하시오\n";
        System.out.println(str);
    }

    private static void initDatabase() {
        try{
//            Class.forName("com.my sql.jdbc.Driver");

            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/smu?useUnicode=true&serverTimezone=Asia/Seoul",
                    "root",
                    "kl;'");

            stmt = conn.createStatement();



        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
