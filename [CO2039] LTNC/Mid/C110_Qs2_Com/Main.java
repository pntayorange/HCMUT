package Paws.CO2039_LTNC.C110_Qs2_Com;

// javac -d . Paws/CO2039_LTNC/C110_Qs2_Com/*.java

//  java Paws.CO2039_LTNC.C110_Qs2_Com.Main

public class Main {
    public static void main(String[] args) {
        Triangle baseTriangle = new Triangle(3.0, 4.0);
        Pyramid pyramid = new Pyramid(baseTriangle, 5.0);
        System.out.println(pyramid.getVolume());
        System.out.println(pyramid.getPyramidHeight());
    }
}
