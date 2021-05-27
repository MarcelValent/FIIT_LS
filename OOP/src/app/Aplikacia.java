package app;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import model.Storage.Storage;

import java.util.Objects;

public class Aplikacia extends Application {
    /**
     * @param primaryStage okno
     * @throws Exception
     * spustí aplikáciu
     * @author Marcel Valent
     */
    @Override
    public void start(Stage primaryStage) throws Exception {

            // @Aggregation - vytvorenie skladu
            Storage storage = Storage.getInstance();
            storage.loadStorage();
            //spustenie prveho okna
            Parent root = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("../view/AplikaciaView.fxml")));
            Scene scene = new Scene(root);
            primaryStage.setScene(scene);
            primaryStage.getIcons().add(new Image("/utils/auto.png"));
            primaryStage.setTitle("CleanCar");
            primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
