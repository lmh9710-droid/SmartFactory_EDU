package com.example;

import java.util.Scanner;

public class Run {
    
    static void Activate(){
      Scanner sc = new Scanner(System.in);
      String url = "jdbc:sqlite:data/study.db";
      //정보입력
      System.out.print("책제목 입력: ");
      String title = sc.nextLine();

      System.out.print("책저자 입력: ");
      String author = sc.nextLine();

      System.out.print("책가격 입력: ");
      int price = sc.nextInt();

      //삽입 개체 인스턴스
      InsertTest.addBook(title, author, price, url);
      sc.close();
    }
}
