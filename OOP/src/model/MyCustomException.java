package model;

import javafx.scene.control.Alert;

/**
 * moja vlastna vynimka
 */
public class MyCustomException extends Exception
{
    /**
     * @param error string ktory chceme vypisat v danom okne
     */
    public MyCustomException(String error)
    {
        super(error);
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Error");
        alert.setHeaderText(null);
        alert.setContentText(error);
        alert.showAndWait();
    }
}