package Paws.CO2039_LTNC.C110_Qs2_Com;

public class Triangle {
    double base;
    double height;

    public Triangle(double base, double height) {
        this.base = base;
        this.height = height;
    }

    public double getBase() {
        return this.base;
    }

    public double getHeight() {
        return this.height;
    }

    public double getArea() {
        return 0.5 * base * height;
    }
}
