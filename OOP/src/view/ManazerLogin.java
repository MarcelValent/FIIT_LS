package view;

import controller.ManagerLoginController;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;


/**
 * okno pre prihlasenie manazera
 */
public class ManazerLogin extends Stage {

    /**
     * @param primarystage
     * JAVAFX GUI
     */
    public void start(Stage primarystage) {
        Label label = new Label("Zadajte ID pre prihlásenie");
        GridPane boxik = new GridPane();
        TextField idcko = new TextField();
        primarystage.setTitle("CleanCar");
        Button tlacitko = new Button ("Prihlásiť");
        tlacitko.setOnAction(e -> {
            ManagerLoginController.prihlasuj(idcko.getText());
        });
        boxik.setPadding(new Insets(175,10,10,225));
        GridPane.setConstraints(label,0,1);
        GridPane.setConstraints(idcko,0,2);
        GridPane.setConstraints(tlacitko,0,3);
        Stage scroll= new Stage();
        scroll.setTitle("CleanCar");
        scroll.getIcons().add(new Image("utils/auto.png"));
        boxik.getChildren().addAll(tlacitko,idcko,label);
        Scene scena = new Scene(boxik,600,400);
        scroll.setScene(scena);
        scroll.show();
    }
}

