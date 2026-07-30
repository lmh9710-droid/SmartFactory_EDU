import streamlit as st

from src import queries, services, ui

df = queries.production_materials(production_id= 1)
ui.show_dataframe(df)
