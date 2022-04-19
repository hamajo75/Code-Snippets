/**
* \brief Replace or insert container element
*
* Replace existing element or insert element if it doesn't exist.
* "predicate" defines what it means, that the element already exists
* (e.g. c[i].Id == e.Id).
*
* Note: It's assumed that the predicate holds only for one element.
*       If that is not so, only the first element found will be updated.
*
* \param container Container where the element is updated.
* \param element Element to be updated.
* \param predicate Identity criterion.
*/
template<class C, typename T>
void UpdateElement(C* container, T element, std::function<bool(typename C::value_type)> predicate) {
  auto entry = std::find_if(container->begin(), container->end(), predicate);
  if (entry == container->end()) {
    container->insert(container->end(), element);
  } else {
    *entry = element;
  }
}
/**
* \brief Erase all elements for which predicate holds.
*
* \param container Container from which the element is removed.
* \param predicate Erase criterion.
*/
template<class C>
void EraseElements(C* container, std::function<bool(typename C::value_type)> predicate) {
  container->erase(
    std::remove_if(container->begin(), container->end(), predicate),
    container->end());
}
