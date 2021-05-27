package controller;

import javafx.stage.Stage;
import model.MyCustomException;
import view.ManagerView;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * controller pre prihlasenie manazera
 */
public class ManagerLoginController {


    /**
     * @param userName načítané meno z textfield
     * @throws FileNotFoundException nenajdeny subor
     * @throws MyCustomException
     * skenovanie textoveho suboru a porovnavanie so zadanou hodnotou
     */
    public static void pomocna(String userName) throws FileNotFoundException, MyCustomException {
        File subor = new File("../CarWash_final/src/utils/ID.txt");
        Scanner scanner = new Scanner(subor);
        while(scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if (userName.equals(line)) {
                Stage manazer = new ManagerView();
                ((ManagerView) manazer).vypis(manazer);
                return;
            }
        }
        throw new MyCustomException("Zadali ste neplatné ID.");
    }

    /**
     * @param userName
     * prihlásenie používateľa
     */
    public static void prihlasuj(String userName)  {
      try{
          pomocna(userName);
      }
      catch (FileNotFoundException b){
          b.printStackTrace();
      }
       catch (MyCustomException e){
          e.printStackTrace();
       }
    }
}



