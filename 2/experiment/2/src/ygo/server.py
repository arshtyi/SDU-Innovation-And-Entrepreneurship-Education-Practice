from mcp.server.fastmcp import FastMCP
from ygoutil.source import BaiGe

mcp = FastMCP("ygo_card_baige")


@mcp.tool()
async def query_ygo_card(query: str) -> str | None:
    """
    通过 query 查询，得到一张游戏王卡的信息
    """
    source = BaiGe()
    card = await source.from_query(query)
    if card is None:
        return None
    return card.info()


if __name__ == "__main__":
    mcp.run()
