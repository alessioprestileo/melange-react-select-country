open DropdownIndicator;
open MenuList;
open SelectOption;
open ReactSelect;
open SharedStyles;
open Types;

module type DropdownMenu = {
  [@react.component]
  let make:
    (
      ~options: array(Types.countryJsCompatible),
      ~value: Js.nullable(Types.countryJsCompatible),
      ~onChange: Types.countryJsCompatible => unit
    ) =>
    React.element;
};
module DropdownMenu: DropdownMenu = {
  module Styles = {
    let rootContainer =
      ReactDOM.Style.make(
        ~position="absolute",
        ~zIndex="2",
        ~marginTop="2px",
        (),
      );
    let select: ReactSelect.customStylesMap(ReactDOM.Style.t) = {
      container:
        ReactDOM.Style.make(
          ~width="230px",
          ~color=SharedStyles.Colors.textPrimary,
          (),
        ),
      control:
        ReactDOM.Style.make(
          ~flexDirection="row-reverse",
          ~minHeight="26px",
          ~padding="0px 10px",
          ~alignItems="center",
          ~flexShrink="0",
          ~alignSelf="stretch",
          ~height="38px",
          ~borderRadius="2px",
          ~borderStyle="none",
          ~borderWidth="1px",
          ~borderBottomLeftRadius="0",
          ~borderBottomRightRadius="0",
          ~boxShadow=
            "0px 3px 18px 0px "
            ++ SharedStyles.Colors.shadow
            ++ ", 0px 0px 0px 1px "
            ++ SharedStyles.Colors.borderLight,
          (),
        ),
      input: SharedStyles.makeStyleWithTextPrimary(~height="18px", ()),
      menu:
        ReactDOM.Style.make(
          ~margin="0",
          ~borderRadius="2px",
          ~borderStyle="none",
          ~borderWidth="1px",
          ~borderTopLeftRadius="0",
          ~borderTopRightRadius="0",
          ~boxShadow=
            "0px 7px 14px -2px "
            ++ SharedStyles.Colors.shadow
            ++ ", 0px 0px 0px 1px "
            ++ SharedStyles.Colors.borderLight,
          (),
        ),
      menuList: ReactDOM.Style.make(~maxHeight="365px", ()),
      option:
        SharedStyles.makeStyleWithTextPrimary(
          ~padding="4px 6px 4px 10px",
          ~color=SharedStyles.Colors.textPrimary,
          (),
        ),
      placeholder:
        SharedStyles.makeStyleWithTextPrimary(
          ~height="14px",
          ~flex="1 0 0",
          ~overflow="hidden",
          ~color=SharedStyles.Colors.textTertiary,
          ~textOverflow="ellipsis",
          ~whiteSpace="nowrap",
          (),
        ),
      valueContainer:
        ReactDOM.Style.make(
          ~padding="0",
          ~height="28px",
          ~fontSize="14px",
          ~alignItems="center",
          (),
        ),
    };
  };
  [@react.component]
  let make =
      (
        ~options: array(Types.countryJsCompatible),
        ~value: Js.nullable(Types.countryJsCompatible),
        ~onChange: Types.countryJsCompatible => unit,
      ) => {
    <div style=Styles.rootContainer>
      <ReactSelect
        options
        value
        onChange
        styles={
          container: (baseStyles, _) =>
            ReactDOM.Style.combine(baseStyles, Styles.select.container),
          control: (baseStyles, _) =>
            ReactDOM.Style.combine(baseStyles, Styles.select.control),
          input: (baseStyles, _) =>
            ReactDOM.Style.combine(baseStyles, Styles.select.input),
          menu: (baseStyles, _) =>
            ReactDOM.Style.combine(baseStyles, Styles.select.menu),
          menuList: (baseStyles, _) =>
            ReactDOM.Style.combine(baseStyles, Styles.select.menuList),
          option: (baseStyles, state) =>
            baseStyles
            ->ReactDOM.Style.combine(Styles.select.option)
            ->ReactDOM.Style.combine(
                if (state.isFocused || state.isSelected) {
                  ReactDOM.Style.make(
                    ~backgroundColor=SharedStyles.Colors.backgroundSelected,
                    (),
                  );
                } else {
                  ReactDOM.Style.make();
                },
              ),
          placeholder: (baseStyles, _) =>
            ReactDOM.Style.combine(baseStyles, Styles.select.placeholder),
          valueContainer: (baseStyles, _) =>
            ReactDOM.Style.combine(baseStyles, Styles.select.valueContainer),
        }
        components={
          "DropdownIndicator": Js.Nullable.return(DropdownIndicator.render),
          "IndicatorSeparator": Js.Nullable.null,
          "MenuList": Js.Nullable.return(MenuList.render),
          "Option": Js.Nullable.return(SelectOption.render),
        }
        autoFocus=true
        placeholder="Search"
        menuIsOpen=true
        tabSelectsValue=false
        controlShouldRenderValue=false
        hideSelectedOptions=false
        isClearable=false
      />
    </div>;
  };
};
