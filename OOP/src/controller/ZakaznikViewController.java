package controller;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import model.Umyvacistroj;


/**
 * controller pre pohlad zakaznika
 */
public class ZakaznikViewController {
    Umyvacistroj stroj =new Umyvacistroj();
    @FXML
    Label labelzakaznik;

    /**
     * @param cas
     * táto funkcia spustí multithreading
     */
    public void runThreading(int cas) {
        Runnable thread = new Threading(cas);
        new Thread(thread).start();
    }


    /**
     * pustenie umývacieho stroja v príslušnom móde
     */
    public void gotoOplachumytie(){
        labelzakaznik.setText(stroj.oplachumytie());
        int time= (1000 * stroj.water.getCas());
        runThreading(time);
    }

    /**
     * pustenie umývacieho stroja v príslušnom móde
     */
    public void gotoBasicumytie(){
        labelzakaznik.setText(stroj.basicumytie());
        int time= (1000 * (stroj.water.getCas()+stroj.shampoowater.getCas()));
        runThreading(time);
    }

    /**
     *pustenie umývacieho stroja v príslušnom móde
     */
    public void gotoStandartumytie(){
        labelzakaznik.setText(stroj.standartumytie());
        int time= (1000 * (stroj.water.getCas()+stroj.shampoowater.getCas()+stroj.foam.getCas()+stroj.deinsect.getCas()));
        runThreading(time);
    }

    /**
     *pustenie umývacieho stroja v príslušnom móde
     */
    public void gotoPremiumwash(){
        labelzakaznik.setText(stroj.premiumwash());
        int time= (1000 * (stroj.water.getCas()+stroj.shampoowater.getCas()+stroj.foam.getCas()+stroj.deinsect.getCas()+stroj.wax.getCas()));
        runThreading(time);
    }
}
