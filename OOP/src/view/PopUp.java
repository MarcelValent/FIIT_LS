package view;
import javafx.scene.control.Alert;

/**
 * pop up okno
 */
public class PopUp extends Exception
    {
        /**
         * @param odkaz
         * pop up okno
         */
        public PopUp(String odkaz)
        {
            super(odkaz);
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("CarWash");
            alert.setHeaderText(null);
            alert.setContentText(odkaz);
            alert.showAndWait();
        }
    }

