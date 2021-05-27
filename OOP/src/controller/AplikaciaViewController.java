package controller;


import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import view.ManazerLogin;
import java.io.IOException;
import java.util.Objects;


/**
 * controller pre zaciatocne okno
 */
public class AplikaciaViewController {

    /**
     * @throws IOException
     * prepnutie na zákaznícke menu
     */
    @FXML
public void gotoZakaznik() throws IOException {
    try {

        Parent root = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("../view/ZakaznikView.fxml")));
        Stage primarystage = new Stage();
        primarystage.setTitle("CleanCar");
        primarystage.setScene(new Scene(root,600,400));
        primarystage.show();
    } catch(Exception e) {
        e.printStackTrace();
    }
}

    /**
     * @throws IOException
     * prepnutie na login okno pre manažéra
     */
public void gotoManazerLogin() throws IOException {
    try {
    Stage prihlasenie = new ManazerLogin();
    ((ManazerLogin) prihlasenie).start(prihlasenie);
    prihlasenie.setTitle("CleanCar");
}catch(Exception e) {
        e.printStackTrace();
    }}}




