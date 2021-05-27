package model;

/**
 * vosk
 */
//Inheritance
public class Vosk extends Surovina{
    public Vosk( int spotreba,int cas){
        super(spotreba,cas);
    }

    /**
     * @return
     * ziskanie casu pre umyvaci stroj
     */
    @Override //polymorfizmus- overriding
    public int Umyvanie(){
        int cas=getCas();
        return cas;
    }
}
