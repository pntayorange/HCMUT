package Paws.CO2039_LTNC.C110_Qs2_Inher;

// javac -d . Paws/CO2039_LTNC/C110_Qs2_Inher/*.java

//  java Paws.CO2039_LTNC.C110_Qs2_Inher.Main

public class Main {
    public static void main(String[] args) {
        Pyramid pyramid = new Pyramid(3.0, 4.0, 5.0);
        System.out.println(pyramid.getVolume());
        System.out.println(pyramid.getPyramidHeight());
    }
}
