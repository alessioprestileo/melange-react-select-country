open Types;

module ReactSelect = {
  type customStylesMap('a) = {
    container: 'a,
    control: 'a,
    input: 'a,
    menu: 'a,
    menuList: 'a,
    option: 'a,
    placeholder: 'a,
    valueContainer: 'a,
  };
  type selectOptionState = {
    isFocused: bool,
    isSelected: bool,
  };
  type stylesType =
    customStylesMap(
      (ReactDOM.Style.t, selectOptionState) => ReactDOM.Style.t,
    );
  type selectOption('a) = {
    label: string,
    value: string,
    customFields: 'a,
  };
  type menuListProps('a) = {
    children: Js.Json.t,
    getStyles: (string, menuListProps('a)) => ReactDOM.style,
    innerProps: Js.t({.}),
    focusedOption: Js.Nullable.t(selectOption('a)),
  };
  type menuListChildRecordData('a) = {data: selectOption('a)};
  type menuListChildRecord('a) = {props: menuListChildRecordData('a)};
  type optionProps('a) = {
    children: Js.Json.t,
    getStyles: (string, optionProps('a)) => ReactDOM.style,
    innerProps: Js.t({.}),
    innerRef: ReactDOM.domRef,
    data: selectOption('a),
  };
  type componentsType('a) = {
    .
    "DropdownIndicator": Js.Nullable.t(unit => React.element),
    "IndicatorSeparator": Js.Nullable.t(unit => React.element),
    "MenuList": Js.Nullable.t(menuListProps('a) => React.element),
    "Option": Js.Nullable.t(optionProps('a) => React.element),
  };
  [@mel.module "react-select"] [@react.component]
  external make:
    (
      ~autoFocus: bool,
      ~components: componentsType('a),
      ~controlShouldRenderValue: bool,
      ~hideSelectedOptions: bool,
      ~isClearable: bool,
      ~menuIsOpen: bool,
      ~onChange: Types.countryJsCompatible => unit,
      ~options: array(Types.countryJsCompatible),
      ~placeholder: string,
      ~styles: stylesType,
      ~tabSelectsValue: bool,
      ~value: Js.nullable(Types.countryJsCompatible)
    ) =>
    React.element =
    "default";
};
