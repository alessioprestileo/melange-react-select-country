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
  type menuListProps = {
    children: Js.Json.t,
    getStyles: (string, menuListProps) => ReactDOM.style,
    innerProps: Js.t({.}),
    focusedOption: Js.Nullable.t(Types.countryJsCompatible),
  };
  type optionProps = {
    children: Js.Json.t,
    getStyles: (string, optionProps) => ReactDOM.style,
    innerProps: Js.t({.}),
    innerRef: ReactDOM.domRef,
    data: Types.countryJsCompatible,
  };
  type componentsType = {
    .
    "DropdownIndicator": Js.Nullable.t(unit => React.element),
    "IndicatorSeparator": Js.Nullable.t(unit => React.element),
    "MenuList": Js.Nullable.t(menuListProps => React.element),
    "Option": Js.Nullable.t(optionProps => React.element),
  };
  [@mel.module "react-select"] [@react.component]
  external make:
    (
      ~autoFocus: bool,
      ~components: componentsType,
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
