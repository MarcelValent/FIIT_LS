package view;


import controller.ManagerViewController;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.image.Image;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;


/**
 * GUI pre manazera
 */
public class ManagerView extends Stage {
    public static TextArea storagetext;

    /**
     * @param primarystage
     * JAVAFX GUI
     */
    public void vypis(Stage primarystage) {
        GridPane boxik = new GridPane();
        primarystage.setTitle("CleanCar");
        storagetext = new TextArea();
        Button tlacitko = new Button ("Vypíš sklad");
        Button tlacitko2 = new Button ("Dopln zásoby");
        boxik.setPadding(new Insets(175,10,10,225));
        tlacitko.setOnAction(e -> {
            ManagerViewController.sklad();
        });
        tlacitko2.setOnAction(b -> {
            ManagerViewController.restock();
        });
        boxik.setHgap(-100);
        boxik.setVgap(30);
        boxik.setPadding(new Insets(30,0,0,75));
        GridPane.setConstraints(storagetext,0,1);
        GridPane.setConstraints(tlacitko,0,2);
        GridPane.setConstraints(tlacitko2,1,2);
        Stage scroll= new Stage();
        boxik.getChildren().addAll(tlacitko,tlacitko2,storagetext);
        Scene scena = new Scene(boxik,600,400);
        scroll.setScene(scena);
        scroll.setTitle("CleanCar");
        scroll.getIcons().add(new Image("utils/auto.png"));
        scroll.show();
    }
}
