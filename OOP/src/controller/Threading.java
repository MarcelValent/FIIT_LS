package controller;

import javafx.application.Platform;
import view.PopUp;

/**
 * multithreading
 */
public class Threading implements Runnable{
    int cas=0;

    /**
     * @param cas
     * definovanie času, po ktorú má byť thread nečinný
     */
    public Threading(int cas){
        this.cas=cas;
    }


    /**
     * spustenie multithreading, následne zobrazí pop up okno
     */
    @Override
    public void run() {
        try {
            Thread.sleep(cas);
            //lambda výraz
            Platform.runLater(() -> {
                cas=(cas/1000);
                new PopUp("Požadovaný program bol úspešne dokončený.");
            });
        }
        catch (Exception ignored) {
        }
    }
}