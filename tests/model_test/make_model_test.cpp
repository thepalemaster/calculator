#include "model_test.hpp"
#include "shape_areas.hpp"


int main() {
    Shapes::Rectangle rect(0);
    ShapeModel rectModel(rect.getOptions());
    ModelAsserts rectAModel;
    rectAModel.name[0] = "Прямоугольник";
    rectAModel.paramNumbers = 2; 
    rectAModel.setDoubleName("Сторона А", 1);
    rectAModel.setDoubleName ("Сторона Б", 2);
    rectAModel.format[0] = "Прямоугольник S: %g (%g × %g)";
    rectAModel.shortNames.push_back("rect");
    std::cout << "---Rectangle---\n";
    make_test_for_model(rectModel, rectAModel);
    std::cout << '\n';
    
    Shapes::Circle circl(0);
    ShapeModel circlModel(circl.getOptions());
    ModelAsserts circlAModel;
    circlAModel.name[0] = "Круг";
    circlAModel.setDoubleName("Диаметр", 1);
    circlAModel.format[0] = "Круг S: %g, D: %g";
    circlAModel.paramNumbers = 1;
    circlAModel.shortNames.push_back("circle");
    std::cout << "---Circle---\n";
    make_test_for_model(circlModel, circlAModel);
    std::cout << '\n';
    
    Shapes::Cylinder cyl(0);
    ShapeModel cylModel(cyl.getOptions());
    ModelAsserts cylAModel;
    cylAModel.name[0] = "Цилиндр";
    cylAModel.setDoubleName ("Высота", 1);
    cylAModel.setDoubleName ("Диаметр", 2);
    cylAModel.paramNumbers = 2;
    cylAModel.format[0] = "Цилиндр S: %g, h: %g, D: %g";
    cylAModel.shortNames.push_back("cyl");
    std::cout << "---Cylinder---\n";
    make_test_for_model(cylModel, cylAModel);
    std::cout << '\n';
    
    Shapes::Sphere sphr(0);
    ShapeModel sphrModel(sphr.getOptions());
    ModelAsserts sphrAModel;
    sphrAModel.name[0] = "Шар";
    sphrAModel.paramNumbers = 1;
    sphrAModel.setDoubleName("Диаметр", 1);
    sphrAModel.format[0] = "Шар S: %g, D: %g";
    sphrAModel.shortNames.push_back("sphere");
    std::cout << "---Sphere---\n";
    make_test_for_model(sphrModel, sphrAModel);
    std::cout << '\n';
    

    Shapes::Hexagon hex(0);
    ShapeModel hexModel(hex.getOptions());
    ModelAsserts hexAModel;
    hexAModel.name[0] = "Шестиугольник";
    hexAModel.setDoubleName("Диаметр вписанной окружности", 1);
    hexAModel.setDoubleNameOneOption("Диаметр описанной окружности", 1, true);
    hexAModel.paramNumbers = 1;
    hexAModel.setFormat("Шестиугольник S: %g, d(вписаная): %g");
    hexAModel.setFormatOneOption("Шестиугольник S: %g, D(описаная): %g", true);
    hexAModel.boolNames[0] = "Описанная окружность";
    hexAModel.shortNames.push_back("hex");
    std::cout << "---Hexagon---\n";
    make_test_for_model(hexModel, hexAModel);
    std::cout << '\n';
    

    Shapes::Bushing bush(0); 
    ShapeModel bushModel(bush.getOptions());
    ModelAsserts bushAModel;
    bushAModel.name[0] = "Втулка";
    bushAModel.paramNumbers = 3;
    bushAModel.setDoubleName ("Диаметр втулки", 1);
    bushAModel.setDoubleName ("Диаметр отверстия", 2);
    bushAModel.setDoubleName ("Высота втулки", 3);
    bushAModel.format[0] = "Втулка S: %g, D: %g, d: %g, h: %g";
    bushAModel.shortNames.push_back("bushing");
    std::cout << "---Bushing---\n";
    make_test_for_model(bushModel, bushAModel);
    std::cout << '\n';
    
    Shapes::HexPrism hexp(0);
    ShapeModel hexpModel(hexp.getOptions());
    ModelAsserts hexpAModel;
    hexpAModel.name[0] = "Призма (N=6)";
    hexpAModel.paramNumbers = 2;
    hexpAModel.setDoubleName("Диаметр вписанной окружности", 1);
    hexpAModel.setDoubleNameOneOption("Диаметр описанной окружности", 1, true);
    hexpAModel.setDoubleNameNoOptions("Высота призмы", 2);
    hexpAModel.setFormat("Боковые грани призмы N=6  S: %g, d: %g h: %g");
    hexpAModel.setFormatOneOption("Боковые грани призмы N=6  S: %g, D: %g h: %g", true); 
    hexpAModel.boolNames[0] = "Описанная окружность";
    std::cout << "---Hexagon Prism---\n";
    hexpAModel.shortNames.push_back("hexprism");
    make_test_for_model(hexpModel, hexpAModel);
    std::cout << '\n';
    
    Shapes::Cuboid cube(0);
    ShapeModel cubeModel(cube.getOptions());
    ModelAsserts cubeAModel;
    cubeAModel.name[0] = "Параллелепипед";
    cubeAModel.paramNumbers = 3;
    cubeAModel.setDoubleName ("Сторона A", 1);
    cubeAModel.setDoubleName ("Сторона B", 2);
    cubeAModel.setDoubleName ("Сторона C", 3);
    cubeAModel.format[0] = "Параллелепипед(кубоид) S: %g, A: %g, B: %g, C: %g";
    cubeAModel.shortNames.push_back("cuboid");
    std::cout << "---Cuboid---\n";
    make_test_for_model(cubeModel, cubeAModel);
    std::cout << '\n';
    
    Shapes::Triangle triang(0);
    ShapeModel triangModel(triang.getOptions());
    ModelAsserts triangAModel;
    triangAModel.name[0] = "Треугольник";
    triangAModel.paramNumbers = 2;
    triangAModel.setDoubleName("Основание треугольника", 1);
    triangAModel.setDoubleName("Высота треугольника", 2);
    triangAModel.boolNames[0] = "Через длинны сторон";
    triangAModel.boolNames[1] = "Через углы треугольника";
    triangAModel.setDoubleNameTwoOptions("Сторона a", 1, true, false);
    triangAModel.setDoubleNameTwoOptions("Сторона b", 2, true, false);
    triangAModel.setDoubleNameTwoOptions("Сторона c", 3, true, false);
    triangAModel.setDoubleNameTwoOptions("Сторона a", 1, false, true);
    triangAModel.setDoubleNameTwoOptions("Угол α", 2, false, true);
    triangAModel.setDoubleNameTwoOptions("Угол β", 3, false, true);
    triangAModel.setDoubleNameTwoOptions("Сторона a", 1, true, true);
    triangAModel.setDoubleNameTwoOptions("Сторона b", 2, true, true);
    triangAModel.setDoubleNameTwoOptions("Угол α", 3, true, true);
    triangAModel.setFormat("Треугольник S: %g, b: %g, h: %g");
    triangAModel.setFormatTwoOptions("Треугольник S: %g, a: %g, b: %g, c: %g", true, false);
    triangAModel.setFormatTwoOptions("Треугольник S: %g, a: %g, α: %g, β: %g", false, true);
    triangAModel.setFormatTwoOptions("Треугольник S: %g, a: %g, b: %g, α: %g", true, true);
    std::cout << "---Triangle---\n";
    triangAModel.shortNames.push_back("triangle");
    make_test_for_model(triangModel, triangAModel);
    std::cout << '\n';
    
}
