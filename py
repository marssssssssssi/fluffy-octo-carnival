class ItemContainer:
    def __init__(self, mass, cost):
        self.mass = mass
        self.cost = cost
        self.efficiency = cost / mass if mass > 0 else 0

def solve_knapsack_problem(item_list, max_capacity):
    # Сортируем элементы по эффективности (стоимость за единицу веса)
    sorted_items = sorted(item_list, 
                         key=lambda elem: elem.efficiency, 
                         reverse=True)
    
    current_capacity = max_capacity
    accumulated_value = 0.0
    selected_items = []
    
    for current_item in sorted_items:
        if current_capacity <= 0:
            break
            
        item_mass = current_item.mass
        item_value = current_item.cost
        
        if item_mass <= current_capacity:
            # Полностью помещаем предмет
            selected_items.append((item_mass, item_value))
            accumulated_value += item_value
            current_capacity -= item_mass
        else:
            # Берем только часть предмета
            fraction_used = current_capacity / item_mass
            partial_value = item_value * fraction_used
            selected_items.append((current_capacity, partial_value))
            accumulated_value += partial_value
            current_capacity = 0
    
    return accumulated_value, selected_items

# Тестовые данные
test_items = [
    ItemContainer(2, 10),
    ItemContainer(3, 20), 
    ItemContainer(4, 15),
    ItemContainer(5, 25)
]
backpack_capacity = 8

final_value, selection = solve_knapsack_problem(test_items, backpack_capacity)
print(f"Полученная суммарная стоимость: {final_value}")
print("Отобранные элементы (масса, стоимость):")
for mass, cost in selection:
    print(f"Масса: {mass}, Ценность: {cost}")
