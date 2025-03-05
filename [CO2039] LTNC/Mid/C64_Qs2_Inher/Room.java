package Paws.CO2039_LTNC.Inher;

public class Room {
    private String name;
    private double area;

    public Room(String name, double area) {
        this.name = name;
        this.area = area;
    }

    public String getName() {
        return this.name;
    }

    public double getArea() {
        return this.area;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setArea(double area) {
        this.area = area;
    }
}
