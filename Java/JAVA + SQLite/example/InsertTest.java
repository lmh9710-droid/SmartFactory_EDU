package com.example;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;


public class InsertTest {
    static void addBook(String title, String author, int price, String url){
        String sql = "insert into book(title, author, price) values(?, ?, ?)";
        try(Connection con = DriverManager.getConnection(url);
            PreparedStatement ps = con.prepareStatement(sql))
        {  
            ps.setString(1, title);
            ps.setString(2, author);
            ps.setInt(3, price);
            ps.executeUpdate();
        }

        catch(Exception e) {

            System.out.println("예외처리좀 그만해라");
        }
    }
}
