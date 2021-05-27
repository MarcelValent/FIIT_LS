package model;

/**
 * pena
 */
//Inheritance
public class Pena extends Surovina{
    public Pena( int spotreba,int cas){
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
