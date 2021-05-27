package model;

/**
 * samponova voda
 */
//Inheritance
public class Jarovavoda extends Surovina {

    public Jarovavoda( int spotreba, int cas) {
        super( spotreba, cas);
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
