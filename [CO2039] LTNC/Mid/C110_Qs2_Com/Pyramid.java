package Paws.CO2039_LTNC.C110_Qs2_Com;

public class Pyramid {
    private Triangle baseTriangle;
    private double pyramidHeight;

    public Pyramid(Triangle baseTriangle, double pyramidHeight) {
        this.baseTriangle = baseTriangle;
        this.pyramidHeight = pyramidHeight;
    }

    public double getPyramidHeight() {
        return this.pyramidHeight;

    }

    public double getVolume() {
        return 1.0 / 3.0 * baseTriangle.getArea() * pyramidHeight;
    }
}
