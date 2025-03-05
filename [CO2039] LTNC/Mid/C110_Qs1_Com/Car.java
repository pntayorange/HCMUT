package Paws.CO2039_LTNC.C110_Qs1_Com;

public class Car {
    private String model;
    private Engine engine;

    public Car(Engine engine) {
        this.model = "Unknown Model"; // Dont need
        this.engine = engine;
    }

    public Car(String model, String engineType, int engineHorsepower) {
        this.model = model;
        this.engine = new Engine(engineType, engineHorsepower);
    }

    public Engine getEngine() {
        return engine;
    }

    public String getModel() {
        return model;
    }

    public void setEngine(Engine engine) {
        this.engine = engine;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public void drive() {
        System.out.println("Car model " + this.getModel() + " is driving");
    }

    public void getEngineInfo() {
        System.out.println("Car engine is " + this.getEngine().getType() + " type and has " + this.getEngine().getHorsePower() + " hp");
    }
}
