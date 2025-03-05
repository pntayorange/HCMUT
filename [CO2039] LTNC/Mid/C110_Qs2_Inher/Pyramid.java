package Paws.CO2039_LTNC.C110_Qs2_Inher;

public class Pyramid extends Triangle {
    private double pyramidHeight;

    public Pyramid(double base, double height , double pyramidHeight) {
        super(base, height);
        this.pyramidHeight = pyramidHeight;
    }

    public double getPyramidHeight() {
        return this.pyramidHeight;
    }

    public double getVolume() {
        return 1.0 / 3.0 * this.getArea() * this.pyramidHeight;
    }
}
