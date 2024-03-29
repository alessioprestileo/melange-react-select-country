open ReactSelect;
open Spread;
open Types;

module type MenuList = {
  let render:
    ReactSelect.menuListProps(Types.customFieldsJsCompatible) => React.element;
};
module MenuList = {
  module Utils = {
    let getSlicedChildren =
        (~children, ~focusedIndex, ~setScrollValue, ~scrollStep, ~scrollValue) => {
      let scrollIndex =
        int_of_float(float_of_int(scrollValue) /. float_of_int(scrollStep));
      let maxRenderedItems = 14;
      let childrenLength = Array.length(children);
      let maxSliceStart =
        childrenLength > maxRenderedItems
          ? childrenLength - maxRenderedItems : 0;
      let sliceStart =
        focusedIndex === 0
          ? 0 : scrollIndex < maxSliceStart ? scrollIndex : maxSliceStart;
      let maxSliceEnd = childrenLength;
      let sliceEnd =
        sliceStart + maxRenderedItems < maxSliceEnd
          ? sliceStart + maxRenderedItems : maxSliceEnd;
      if (focusedIndex !== (-1)
          && focusedIndex > sliceEnd
          - 1
          && focusedIndex <= maxSliceEnd
          - 1
          && scrollIndex < maxSliceEnd) {
        setScrollValue(prevScrollValue => {
          let scrollDiff = scrollStep * (focusedIndex - sliceEnd + 1);
          let nextScrollValue = prevScrollValue + scrollDiff;
          let maxScrollValue = maxSliceEnd * scrollStep;
          nextScrollValue <= maxScrollValue ? nextScrollValue : maxScrollValue;
        });
      };

      if (focusedIndex !== (-1) && focusedIndex <= sliceStart - 1) {
        let scrollDiff = scrollStep * (sliceStart - focusedIndex);
        setScrollValue(prevScrollValue => prevScrollValue - scrollDiff);
      };

      Array.sub(children, sliceStart, sliceEnd - sliceStart);
    };
  };

  type childRecord =
    ReactSelect.menuListChildRecord(Types.customFieldsJsCompatible);

  let render =
      (props: ReactSelect.menuListProps(Types.customFieldsJsCompatible)) => {
    let rawChildren = props.children;
    let getStyles = props.getStyles;
    let innerProps = props.innerProps;
    let defaultStyle = getStyles("menuList", props);
    let childrenElements: array(React.element) =
      rawChildren->Js.Json.decodeArray->Belt.Option.getWithDefault([||])
      |> Obj.magic;
    let childrenLength = Array.length(childrenElements);
    let childrenRecords: array(childRecord) =
      rawChildren->Js.Json.decodeArray->Belt.Option.getWithDefault([||])
      |> Obj.magic;

    let (scrollValue, setScrollValue) = React.useState(() => 0);
    React.useEffect1(
      () => {
        setScrollValue(_ => 0);
        None;
      },
      [|childrenLength|],
    );

    let scrollStep = 400;
    let handleWheel = e => {
      let deltaY = int_of_float(ReactEvent.Wheel.deltaY(e));
      setScrollValue(prevScrollValue =>
        if (prevScrollValue + deltaY < 0) {
          0;
        } else if (prevScrollValue + deltaY > scrollStep * childrenLength) {
          scrollStep * childrenLength;
        } else {
          prevScrollValue + deltaY;
        }
      );
    };

    let focusedIndex =
      Array.find_index(
        (item: childRecord) =>
          switch (Js.Nullable.toOption(props.focusedOption)) {
          | None => false
          | Some(focusedOption) =>
            item.props.data.value === focusedOption.value
          },
        childrenRecords,
      )
      ->Belt.Option.getWithDefault(-1);

    let allPropsToSpread =
      Js.Obj.assign(
        innerProps,
        {"data-countryselect-component": "menuList"},
      );
    let slicedChildren =
      Utils.getSlicedChildren(
        ~children=childrenElements,
        ~focusedIndex,
        ~setScrollValue,
        ~scrollStep,
        ~scrollValue,
      );

    <Spread props=allPropsToSpread>
      <div onWheel=handleWheel style=defaultStyle>
        {React.array(slicedChildren)}
      </div>
    </Spread>;
  };
};
