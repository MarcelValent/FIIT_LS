package controller;

import model.Storage.Storage;
import view.ManagerView;

/**
 * controller pre pohlad manazera
 */
public class ManagerViewController {
    /**
     *vypísanie obsahu skladu do textového pola
     */
    public static void sklad(){
        ManagerView.storagetext.setText(null);
        ManagerView.storagetext.appendText("Sklad momentálne obsahuje:\n");
        ManagerView.storagetext.appendText("Voda: "+ String.valueOf(Storage.instance.getWater()) + "\n");
        ManagerView.storagetext.appendText("Šampónový roztok: "+ String.valueOf(Storage.instance.getShampooWater()) + "\n");
        ManagerView.storagetext.appendText("Pena: "+ String.valueOf(Storage.instance.getFoam()) + "\n");
        ManagerView.storagetext.appendText("Odhmyzovač: "+ String.valueOf(Storage.instance.getDeinsect()) + "\n");
        ManagerView.storagetext.appendText("Vosk: "+ String.valueOf(Storage.instance.getWax()) + "\n");
        ManagerView.storagetext.appendText("Špinavá voda: "+ String.valueOf(Storage.instance.getDirtyWater()) + "\n");
    }

    /**
     *doplnenie produktov do skladu
     */
    public static void restock(){
    Storage.instance.setWater(1000);
    Storage.instance.setShampooWater(500);
    Storage.instance.setFoam(200);
    Storage.instance.setDeinsect(200);
    Storage.instance.setWax(200);
    Storage.instance.setDirtyWater(0);
    Storage.instance.saveStorage();
    }



}
