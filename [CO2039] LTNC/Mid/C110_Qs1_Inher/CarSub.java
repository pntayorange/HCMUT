package Paws.CO2039_LTNC.C110_Qs1_Inher;

public class CarSub extends Engine {
    private String model;

    public CarSub(String model, String engineType, int engineHorsepower) {
        super(engineType, engineHorsepower);
        this.model = model;
    }

    public CarSub(String model, Engine engine) {
        super(engine.getType(), engine.getHorsePower());
        this.model = model;
    }

    // Where superclass Point?
    public String toString() {
        return "Car model: " + this.getModel() + ", Engine type: " + this.getType() + ", Horsepower: " + this.getHorsePower();

    }

    public String getModel() {
        return this.model;
    }

    public void setEngine(Engine engine) {
        this.setType(engine.getType());
        this.setHorsePower(engine.getHorsePower());
    }

    public void setModel(String model) {
        this.model = model;
    }

    public void drive() {
        System.out.println("Car model " + this.getModel() + " is driving");
    }

    public void getEngineInfo() {
        System.out.println("Car engine is " + this.getType() + " type and has " + this.getHorsePower() + " hp");
    }
}
