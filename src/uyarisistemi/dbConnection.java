/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package uyarisistemi;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import uyarisistemi.model.sensor;
import uyarisistemi.model.veri;


/**
 *
 * @author Burcu
 */
public class dbConnection {
    public Connection connection;
    public void baglan() throws SQLException{
        String url = "jdbc:mysql://localhost:3306/uyariDB";
        String username = "root";
        String password = "1234";
        System.out.println("Connecting database...");
        this.connection = DriverManager.getConnection(url, username, password); 
    }
    public boolean girisKontrol(String k_adi,String parola) throws SQLException, ClassNotFoundException{
        baglan();
        Statement stmt = connection.createStatement();
        ResultSet rs;
        rs = stmt.executeQuery("SELECT * FROM uyariDB.kullanici");
        
        while (rs.next()) {
        String k = rs.getString("k_adi");
        String p = rs.getString("parola");
        if(k.equals(k_adi) && p.equals(parola)){
            return true;
        }
        }
        return false;
        
        
    }
    public void vt_gelen_kaydet(String sic,String gaz) throws SQLException{
        baglan();
      
          PreparedStatement ps = connection.prepareStatement("insert into gelen_sensor(gelen_gaz, gelen_sicaklik ) values(?,?)");
            ps.setString(1, sic);
            ps.setString(2, gaz);
            ps.executeUpdate();
        
        
    }
    public List<sensor> sensor_listele() throws SQLException{
        baglan();
        List<sensor> gelen = new ArrayList<>();
     
        sensor veriler ;
        Statement stmt;
        try {
            stmt = connection.createStatement();
            ResultSet rs;
            rs = stmt.executeQuery("SELECT * FROM gelen_sensor");
           
            while (rs.next()) {
                System.out.println(rs.getString("gelen_sicaklik"));
                System.out.println(rs.getString("gelen_gaz"));
                veriler = new sensor();
                veriler.setSicaklik(rs.getString("gelen_sicaklik"));
                veriler.setGaz(rs.getString("gelen_gaz"));
                
                    gelen.add(veriler);
                
            }
            
            
        } catch (SQLException ex) {
            Logger.getLogger(dbConnection.class.getName()).log(Level.SEVERE, null, ex);
        }
        return gelen;
    }
        public void vt_giden_kaydet(String led,String buz) throws SQLException{
        baglan();
      
          PreparedStatement ps = connection.prepareStatement("insert into giden_sensor(giden_led, giden_buzzer ) values(?,?)");
            ps.setString(1, led);
            ps.setString(2, buz);
            ps.executeUpdate();
        
        
    }
    
      public List<veri> veri_listele() throws SQLException{
        baglan();
        List<veri> gelen = new ArrayList<>();
     
        veri veriler ;
        Statement stmt;
        try {
            stmt = connection.createStatement();
            ResultSet rs;
            rs = stmt.executeQuery("SELECT * FROM giden_sensor");
           
            while (rs.next()) {
                System.out.println(rs.getString("giden_led"));
                System.out.println(rs.getString("giden_buzzer"));
                veriler = new veri();
                veriler.setLed(rs.getString("giden_led"));
                veriler.setBuzzer(rs.getString("giden_buzzer"));
                
                    gelen.add(veriler);
                
            }
            
            
        } catch (SQLException ex) {
            Logger.getLogger(dbConnection.class.getName()).log(Level.SEVERE, null, ex);
        }
        return gelen;
    }
    
}

