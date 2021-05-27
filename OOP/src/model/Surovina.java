package model;

/**
 * abstraktna class z ktorej ostatne suroviny dedia
 */
//abstraktna class
public abstract class Surovina {
        private int spotreba;
        private int cas;


        public Surovina(int spotreba, int cas) {
                this.spotreba=spotreba;
                this.cas=cas;
        }

        /**
         * @return spotreba
         */
        public int Umyvanie() {
                int spotreba = getSpotreba();
                return spotreba;
        }
        //Enkapsulacia
        //Gettery a settery
        /**
         * @return
         * ziskanie spotreby
         */
        public int getSpotreba() {
                return spotreba;
        }

        /**
         * @param spotreba
         * nastavenie spotreby
         */
        public void setSpotreba(int spotreba) {
                this.spotreba = spotreba;
        }

        /**
         * @return
         * ziskanie casu
         */
        public int getCas() {
                return cas;
        }

        /**
         * @param cas
         * nastavenie casu
         */
        public void setCas(int cas) {
                this.cas = cas;
        }

}
